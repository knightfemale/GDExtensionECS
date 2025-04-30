#include "gde_component.h"

using namespace godot;

void GdeComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_component_name", "name"), &GdeComponent::set_component_name);
    ClassDB::bind_method(D_METHOD("get_component_name"), &GdeComponent::get_component_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "component_name"), "set_component_name", "get_component_name");
}

void GdeComponent::_ready() {
    auto parent = get_parent();
    // 检查父节点是否为 GdeEntity
    if (GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent())) {
        entity->add_component(this);
#ifndef DEBUG_DISABLED
        // 打印所有组件
        String components_str = "[GDExtensionECS] Entity: " + String::num_int64(entity->get_instance_id()) + " Components: [";
        for (const auto& pair : entity->components) {
            components_str += String(pair.first.c_str()) + ", ";
        }
        if (!entity->components.empty()) {
            components_str = components_str.substr(0, components_str.length() - 2); // 移除末尾的", "
        }
        UtilityFunctions::print(components_str + "]");
#endif
    }
    else {
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[GDExtensionECS] Warning: Must be child of GdeEntity");
#endif
    }
}

GdeComponent::GdeComponent() {
    //
}

GdeComponent::~GdeComponent() {
    if (GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent())) {
        //entity->remove_component(this);
    }
    else {
#ifndef DEBUG_DISABLED
        UtilityFunctions::print("[GDExtensionECS] Warning: Must be child of GdeEntity");
#endif
}

void GdeComponent::set_component_name(const String& _component_name) {
    component_name = _component_name;
}

String GdeComponent::get_component_name() const {
    return component_name;
}
