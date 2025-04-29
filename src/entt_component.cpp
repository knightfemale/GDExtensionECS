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
        entity = entity_node->get_entity();
        EnttEntity::registry.emplace<EnttComponent*>(entity, this);
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[EnttComponent] Attached ", component_name, " to Entity ID: ", static_cast<uint32_t>(entity));
#endif
    }
    else {
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[EnttComponent] Warning: Must be child of EnttEntity");
#endif
    }
}
EnttComponent::EnttComponent() {
    //
}

EnttComponent::~EnttComponent() {
    if (entity != entt::null) {
        // ´ÓEnTTÒÆ³ý×é¼þ
        EnttEntity::registry.remove<EnttComponent*>(entity);
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[EnttComponent] Removed ", component_name, " from Entity ID: ", static_cast<uint32_t>(entity));
#endif
    }
    else {
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[EnttComponent] Warning: Must be child of EnttEntity");
#endif
    }
}

void EnttComponent::set_component_name(const String& _component_name) {
    component_name = _component_name;
}

String EnttComponent::get_component_name() const {
    return component_name;
}
