#include "gde_system_manager.h"

using namespace godot;

void GdeSystemManager::_bind_methods() {
    //
}

void GdeSystemManager::_ready() {
    systems = get_systems();
    UtilityFunctions::print(systems.size());
}

void GdeSystemManager::_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_physics_process")) continue;
        Dictionary components = get_components_for_system(system);
        system->call("_system_process", components, delta);
    }
}

void GdeSystemManager::_physics_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (!system->has_method("_system_physics_process")) continue;
        Dictionary components = get_components_for_system(system);
        system->call("_system_physics_process", components, delta);
    }
}

Array GdeSystemManager::get_systems() {
    Array result;
    Array children = get_children();
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
    std::vector<std::string> required;
    std::vector<std::string> excluded;

    // 分离必须和排除的组件名称
    for (int i = 0; i < reqs.size(); ++i) {
        String req = reqs[i];
        if (req.begins_with("!")) {
            std::string name = req.substr(1).utf8().get_data();
            excluded.push_back(name);
        }
        else {
            std::string name = req.utf8().get_data();
            required.push_back(name);
        }
    }

    // 获取活跃实体ID
    std::unordered_set<size_t> active_entities;
    {
        std::lock_guard<std::mutex> lock(GdeEntity::entity_id_mutex);
        std::queue<size_t> temp = GdeEntity::free_entity_ids;
        std::unordered_set<size_t> free_ids;
        while (!temp.empty()) {
            free_ids.insert(temp.front());
            temp.pop();
        }
        for (size_t id = 0; id < GdeEntity::next_entity_id; ++id) {
            if (!free_ids.count(id)) active_entities.insert(id);
        }
    }

    // 加锁访问组件数据
    std::lock_guard<std::mutex> comp_lock(GdeEntity::component_mutex);

    for (size_t entity_id : active_entities) {
        bool valid = true;

        // 检查排除组件：实体不能拥有任何排除的组件
        for (const std::string& name : excluded) {
            auto it = GdeEntity::component_type_ids.find(name);
            if (it != GdeEntity::component_type_ids.end()) {
                int type_id = it->second;
                if (type_id < GdeEntity::component_sparse_sets.size() &&
                    GdeEntity::component_sparse_sets[type_id].get(entity_id)) {
                    valid = false;
                    break;
                }
            }
        }
        if (!valid) continue;

        // 检查必须组件：实体必须拥有所有必须的组件
        for (const std::string& name : required) {
            auto it = GdeEntity::component_type_ids.find(name);
            if (it == GdeEntity::component_type_ids.end() ||
                it->second >= GdeEntity::component_sparse_sets.size() ||
                !GdeEntity::component_sparse_sets[it->second].get(entity_id)) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;

        // 收集组件到Dictionary
        for (const std::string& name : required) {
            int type_id = GdeEntity::component_type_ids[name];
            GdeComponent* comp = GdeEntity::component_sparse_sets[type_id].get(entity_id);
            if (comp) {
                String key = String(name.c_str());
                if (!components_dict.has(key)) {
                    components_dict[key] = Array();
                }
                Array arr = components_dict[key];
                arr.append(comp);
                components_dict[key] = arr;
            }
        }
    }

    return components_dict;
}