#include "gde_system_manager.h"

using namespace godot;

std::mutex GdeSystemManager::components_dirty_mutex;
bool GdeSystemManager::components_dirty = false;

void GdeSystemManager::_bind_methods() {
    // 预留方法绑定
}

void GdeSystemManager::mark_components_dirty() {
    std::lock_guard<std::mutex> lock(components_dirty_mutex);
    components_dirty = true;
}

void GdeSystemManager::_ready() {
    systems = get_systems();
}

void GdeSystemManager::_process(double delta) {
    bool need_update = false;
    {
        std::lock_guard<std::mutex> lock(components_dirty_mutex);
        need_update = components_dirty;
        components_dirty = false;
    }

    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_process")) continue;
        if (need_update) update_components(system);
        system->call("_system_process", system->components_dict, system->entity_count, delta);
    }
}

void GdeSystemManager::_physics_process(double delta) {
    bool need_update = false;
    {
        std::lock_guard<std::mutex> lock(components_dirty_mutex);
        need_update = components_dirty;
        components_dirty = false;
    }

    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_physics_process")) continue;
        if (need_update) update_components(system);
        system->call("_system_physics_process", system->components_dict, system->entity_count, delta);
    }
}

Array GdeSystemManager::get_systems() {
    Array result;
    Array children = get_children();
    // 遍历所有子节点, 筛选出 GdeSystem 类型的节点
    for (int i = 0; i < children.size(); ++i) {
        if (GdeSystem* child = Object::cast_to<GdeSystem>(children[i])) {
            result.append(child);
        }
    }
    return result;
}

void GdeSystemManager::update_components(GdeSystem* system) {
    int entity_count = 0;
    Dictionary components_dict;

    // 步骤 1: 直接使用缓存的必须组件和排除组件
    const std::vector<std::string>& required = system->cached_required;
    const std::vector<std::string>& excluded = system->cached_excluded;

    // 步骤 2: 获取所有活跃实体 ID
    std::unordered_set<size_t>& active_entities = GdeEntity::active_entity_ids;

    // 步骤 3: 加锁访问组件数据, 避免并发修改
    std::lock_guard<std::mutex> comp_lock(GdeEntity::component_mutex);

    // 步骤 4: 遍历所有活跃实体进行筛选
    for (size_t entity_id : active_entities) {
        bool valid = true;

        // 子步骤 4.1: 检查排除组件
        for (const std::string& name : excluded) {
            auto it = GdeEntity::component_type_ids.find(name);
            if (it != GdeEntity::component_type_ids.end()) {
                int type_id = it->second;
                // 防御性检查: 确保稀疏集索引有效
                if (type_id >= 0 && type_id < GdeEntity::component_sparse_sets.size()) {
                    // 若实体拥有该排除组件, 标记为无效
                    if (GdeEntity::component_sparse_sets[type_id].get(entity_id)) {
                        valid = false;
                        // 发现无效立即终止循环
                        break;
                    }
                }
            }
        }
        if (!valid) continue;
        // 实体有效，计数器递增

        // 子步骤 4.2: 检查必须组件, 仅当required非空时执行
        if (!required.empty()) {
            for (const std::string& name : required) {
                auto it = GdeEntity::component_type_ids.find(name);
                if (it == GdeEntity::component_type_ids.end()) {
                    // 组件未注册, 实体无效
                    valid = false;
                    break;
                }
                int type_id = it->second;
                // 检查稀疏集范围和组件存在性
                if (type_id < 0 || type_id >= GdeEntity::component_sparse_sets.size() ||
                    !GdeEntity::component_sparse_sets[type_id].get(entity_id)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
        }

        entity_count++;

        // 子步骤 4.3: 收集组件到 Dictionary
        for (const std::string& name : required) {
            auto it = GdeEntity::component_type_ids.find(name);
            if (it == GdeEntity::component_type_ids.end()) continue;
            int type_id = it->second;
            if (type_id < 0 || type_id >= GdeEntity::component_sparse_sets.size()) continue;
            GdeComponent* comp = GdeEntity::component_sparse_sets[type_id].get(entity_id);
            if (comp) {
                String key = String(name.c_str());
                // 避免重复创建Array, 直接操作现有数组
                Array arr = components_dict.get(key, Array());
                arr.append(comp);
                // Godot 的 Array 是写时复制,此处高效
                components_dict[key] = arr;
            }
        }
    }

    // 步骤 5: 将结果存入系统
    system->entity_count = entity_count;
    system->components_dict = components_dict;
}
