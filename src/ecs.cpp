#include "ecs.h"

using namespace godot;

void ECS::_bind_methods() {
    ClassDB::bind_static_method("ECS", D_METHOD("is_component", "node"), &ECS::is_component);
    ClassDB::bind_static_method("ECS", D_METHOD("is_system", "node"), &ECS::is_system);
    ClassDB::bind_static_method("ECS", D_METHOD("is_entity", "node"), &ECS::is_entity);
}

bool ECS::is_component(Node* node) {
    return node->get("component_name") != Variant();
}

bool ECS::is_system(Node* node) {
    return node->get("system_name") != Variant() && node->get("requirements") != Variant();
}

bool ECS::is_entity(Node* node) {
    return node->is_in_group("Entity");
}