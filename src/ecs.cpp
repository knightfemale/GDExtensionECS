#include "ecs.h"

using namespace godot;

HashMap<String, uint32_t> ECS::component_bits;
uint32_t ECS::next_bit = 0;

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

uint32_t ECS::get_component_bit(const String& name) {
    if (!component_bits.has(name)) {
        component_bits[name] = (1ULL << next_bit);
        next_bit++;
        if (next_bit >= 64) {
            UtilityFunctions::printerr("[ECS]: Exceeded 64 component types!");
            next_bit = 63;
        }
    }
    return component_bits[name];
}
