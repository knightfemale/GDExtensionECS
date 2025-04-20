#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "system_manager.h"

using namespace godot;

void SystemManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_node_added", "node"), &SystemManager::_on_node_added);
    ClassDB::bind_method(D_METHOD("_on_node_removed", "node"), &SystemManager::_on_node_removed);
    ClassDB::bind_method(D_METHOD("_on_tree_exited"), &SystemManager::_on_tree_exited);
}

void SystemManager::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) return;

    SceneTree* tree = get_tree();
    tree->connect("node_added", Callable(this, "_on_node_added"));
    tree->connect("node_removed", Callable(this, "_on_node_removed"));
    connect("tree_exited", Callable(this, "_on_tree_exited"));

    systems = get_systems();

    Array entities = tree->get_nodes_in_group("Entity");
    for (int i = 0; i < entities.size(); ++i) {
        update_component_groups(Object::cast_to<Node>(entities[i]));
    }

    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        Node* child = Object::cast_to<Node>(children[i]);
        if (ECS::is_system(child)) {
            System* system = Object::cast_to<System>(child);
            system->precompute_requirements();
            register_requirements(system->get_requirements());
            if (child->has_method("_system_ready")) {
                child->call("_system_ready");
            }
        }
    }
}

void SystemManager::_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        Node* system = Object::cast_to<Node>(systems[i]);
        if (system->has_method("_system_process")) {
            Array entities = query_entities(system);
            system->call("_system_process", entities, delta);
        }
    }
}

void SystemManager::_physics_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        Node* system = Object::cast_to<Node>(systems[i]);
        if (system->has_method("_system_physics_process")) {
            Array entities = query_entities(system);
            system->call("_system_physics_process", entities, delta);
        }
    }
}

void SystemManager::_on_node_added(Node* node) {
    if (ECS::is_component(node)) {
        Node* entity = node->get_parent();
        entity->call("register_component", node);
        update_component_groups(entity);
    }
    else if (ECS::is_entity(node)) {
        update_component_groups(node);
    }
}

void SystemManager::_on_node_removed(Node* node) {
    if (ECS::is_component(node)) {
        Node* entity = node->get_parent();
        entity->call("unregister_component", node);
        update_component_groups(entity);
    }
    else if (ECS::is_entity(node)) {
        update_component_groups(node);
    }
}

void SystemManager::_on_tree_exited() {
    SceneTree* tree = get_tree();
    if (!tree) return;
    tree->disconnect("node_added", Callable(this, "_on_node_added"));
    tree->disconnect("node_removed", Callable(this, "_on_node_removed"));
}

Array SystemManager::get_systems() {
    Array result;
    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        Node* child = Object::cast_to<Node>(children[i]);
        if (ECS::is_system(child)) {
            if (validate_system(child)) {
                result.append(child);
            }
        }
    }
    return result;
}

bool SystemManager::validate_system(Node* system) {
    if (!system->has_method("_system_init")) {
        UtilityFunctions::printerr("[System: ", system->get("system_name"), "] does not have a _system_init() method. Skipping.");
        return false;
    }
    if (!system->call("_system_init", this)) {
        UtilityFunctions::printerr("[System: ", system->get("system_name"), "] _system_init() method returned false. Skipping.");
        return false;
    }
    Array requirements = system->get("requirements");
    if (requirements.is_empty()) {
        UtilityFunctions::printerr("[System: ", system->get("system_name"), "] attempted to register with no requirements. Skipping.");
        return false;
    }
    return true;
}

Array SystemManager::query_entities(Node* system) {
    System* sys = Object::cast_to<System>(system);
    uint64_t require = sys->require_mask;
    uint64_t exclude = sys->exclude_mask;

    for (int i = 0; i < component_groups.size(); ++i) {
        ComponentGroup* group = component_groups[i];
        if (group->require_mask == require && group->exclude_mask == exclude) {
            return group->entities;
        }
    }
    return Array();
}

void SystemManager::register_requirements(const Array& requirements) {
    uint64_t require_mask = 0;
    uint64_t exclude_mask = 0;

    for (int i = 0; i < requirements.size(); ++i) {
        String req = requirements[i];
        if (req.begins_with("!")) {
            String name = req.substr(1);
            exclude_mask |= ECS::get_component_bit(name);
        }
        else {
            require_mask |= ECS::get_component_bit(req);
        }
    }

    bool exists = false;
    for (ComponentGroup* group : component_groups) {
        if (group->require_mask == require_mask && group->exclude_mask == exclude_mask) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        ComponentGroup* new_group = new ComponentGroup();
        new_group->require_mask = require_mask;
        new_group->exclude_mask = exclude_mask;
        new_group->entities = Array();
        component_groups.push_back(new_group);
    }
}

void SystemManager::update_component_groups(Node* entity) {
    uint64_t entity_mask = Object::cast_to<Entity>(entity)->get_component_bitmask();

    for (ComponentGroup* group : component_groups) {
        bool matches = (entity_mask & group->require_mask) == group->require_mask && (entity_mask & group->exclude_mask) == 0;

        if (matches && !group->entities.has(entity)) {
            group->entities.append(entity);
        }
        else if (!matches) {
            group->entities.erase(entity);
        }
    }
}

SystemManager::~SystemManager() {
    for (ComponentGroup* group : component_groups) {
        delete group;
    }
    component_groups.clear();
}
