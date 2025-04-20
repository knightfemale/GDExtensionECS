#include <godot_cpp/classes/engine.hpp>

#include "entity.h"

using namespace godot;

void Entity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &Entity::get_id);
    ClassDB::bind_method(D_METHOD("register_component", "component"), &Entity::register_component);
    ClassDB::bind_method(D_METHOD("unregister_component", "component"), &Entity::unregister_component);
    ClassDB::bind_method(D_METHOD("get_component", "component_name"), &Entity::get_component);
    ClassDB::bind_method(D_METHOD("get_components", "component_name"), &Entity::get_components);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "id", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_READ_ONLY), "", "get_id");
}

void Entity::_ready() {
    if (Engine::get_singleton()->is_editor_hint()) return;

    add_to_group("Entity");
    set_process(false);
    set_physics_process(false);
    set_process_input(false);

    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        register_component(Object::cast_to<Node>(children[i]));
    }
}

void Entity::register_component(Node* component) {
    if (!components.has(component)) {
        String name = component->get("component_name");
        component_bitmask |= ECS::get_component_bit(name);
        components.append(component);
    }
}

void Entity::unregister_component(Node* component) {
    String name = component->get("component_name");
    component_bitmask &= ~ECS::get_component_bit(name);
    components.erase(component);
}

Node* Entity::get_component(const String& component_name) const {
    for (int i = 0; i < components.size(); ++i) {
        Node* component = Object::cast_to<Node>(components[i]);
        if (component->get("component_name") == component_name) {
            return component;
        }
    }
    return nullptr;
}

Array Entity::get_components(const String& component_name) const {
    Array result;
    for (int i = 0; i < components.size(); ++i) {
        Node* component = Object::cast_to<Node>(components[i]);
        if (component->get("component_name") == component_name) {
            result.append(component);
        }
    }
    return result;
}
