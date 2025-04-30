#include "gde_system_manager.h"

using namespace godot;

void GdeSystemManager::_bind_methods() {
    // 预留方法绑定
}

void GdeSystemManager::_ready() {
    systems = get_systems();
}

void GdeSystemManager::_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_process")) continue;
        Dictionary components = get_components_for_system(system);
        if (components.is_empty()) continue;
        system->call("_system_process", components, delta);
    }
}

void GdeSystemManager::_physics_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_physics_process")) continue;
        Dictionary components = get_components_for_system(system);
        if (components.is_empty()) continue;
        system->call("_system_physics_process", components, delta);
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

Dictionary GdeSystemManager::get_components_for_system(GdeSystem* system) {
    Dictionary components_dict;

    Array reqs = system->get_requirements();
    // 必须组件列表
    std::vector<std::string> required;
    // 排除组件列表
    std::vector<std::string> excluded;

    // 步骤 1: 分离必须组件和排除组件
    for (int i = 0; i < reqs.size(); ++i) {
        String req = reqs[i];
        if (req.begins_with("!")) {
            // 处理排除组件: 去掉前缀 "!" 并转换为 std::string
            CharString cs = req.substr(1).utf8();
            excluded.push_back(cs.get_data());
        }
        else {
            // 处理必须组件: 直接转换名称
            CharString cs = req.utf8();
            required.push_back(cs.get_data());
        }
    }

    // 步骤 2: 获取所有活跃实体 ID
    std::unordered_set<size_t> active_entities;
    {
        std::lock_guard<std::mutex> lock(GdeEntity::entity_id_mutex);
        std::queue<size_t> temp = GdeEntity::free_entity_ids;
        std::unordered_set<size_t> free_ids;
        // 缓存所有空闲 ID 以快速判断活跃实体
        while (!temp.empty()) {
            free_ids.insert(temp.front());
            temp.pop();
        }
        // 遍历所有可能的 ID, 筛选出未被回收的实体
        for (size_t id = 0; id < GdeEntity::next_entity_id; ++id) {
            if (!free_ids.count(id)) active_entities.insert(id);
        }
    }

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

    return components_dict;
}