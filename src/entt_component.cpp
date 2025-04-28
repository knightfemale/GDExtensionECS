#include <godot_cpp/variant/utility_functions.hpp>

#include "entt_component.h"

using namespace godot;

void EnttComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_component_name", "name"), &EnttComponent::set_component_name);
    ClassDB::bind_method(D_METHOD("get_component_name"), &EnttComponent::get_component_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "component_name"), "set_component_name", "get_component_name");
}

void EnttComponent::_ready() {
    auto parent = get_parent();
    if (parent->is_class("EnttEntity")) {
        EnttEntity* entity_node = Object::cast_to<EnttEntity>(parent);
        if (entity_node) {
            uint64_t eid = entity_node->get_entity_id();
            entt::entity eid_entt = static_cast<entt::entity>(eid);

            EnttEntity::registry.emplace<EnttComponent*>(eid_entt, this);
            EnttEntity::registry.emplace<String>(eid_entt, component_name);

            UtilityFunctions::print("[EnttComponent] Attached ", component_name, " to Entity ID: ", eid);
        }
    }
    else {
        UtilityFunctions::print("[EnttComponent] Warning: Must be child of EnttEntity");
    }
}

void EnttComponent::set_component_name(const String& p_name) {
    component_name = p_name;
}

String EnttComponent::get_component_name() const {
    return component_name;
}