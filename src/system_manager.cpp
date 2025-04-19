#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "system_manager.h"
#include "ecs.h"

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

    Array entities = tree->get_nodes_in_group("entity");
    for (int i = 0; i < entities.size(); ++i) {
        update_component_groups(Object::cast_to<Node>(entities[i]));
    }

    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        Node* child = Object::cast_to<Node>(children[i]);
        if (ECS::is_system(child)) {
            register_requirements(child->get("requirements"));
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
            Array args;
            args.append(query_entities(system));
            args.append(delta);
            system->callv("_system_process", args);
        }
    }
}

void SystemManager::_physics_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        Node* system = Object::cast_to<Node>(systems[i]);
        if (system->has_method("_system_physics_process")) {
            Array args;
            args.append(query_entities(system));
            args.append(delta);
            system->callv("_system_physics_process", args);
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
            if (Engine::get_singleton()->is_editor_hint()) {
                result.append(child);
            }
            else if (validate_system(child)) {
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
    Array requirements = system->get("requirements");
    requirements.sort();
    return component_groups.get(requirements, Array());
}

void SystemManager::register_requirements(const Array& requirements) {
    Array sorted_req = requirements.duplicate();
    sorted_req.sort();
    if (!component_groups.has(sorted_req)) {
        component_groups[sorted_req] = Array();
    }
}

void SystemManager::update_component_groups(Node* entity) {
    Array keys = component_groups.keys();
    for (int i = 0; i < keys.size(); ++i) {
        Array req = keys[i];
        Array entities = component_groups[req];
        bool meets = entity->call("meets_requirements", req);
        if (meets && !entities.has(entity)) {
            entities.append(entity);
        }
        else if (!meets) {
            entities.erase(entity);
        }
        component_groups[req] = entities;
    }
}