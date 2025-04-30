#include "gde_component.h"

using namespace godot;

void GdeComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_component_name", "name"), &GdeComponent::set_component_name);
    ClassDB::bind_method(D_METHOD("get_component_name"), &GdeComponent::get_component_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "component_name"), "set_component_name", "get_component_name");
}

void GdeComponent::_ready() {
    //
}

GdeComponent::GdeComponent() {
    //
}

GdeComponent::~GdeComponent() {
    //
}

void GdeComponent::set_component_name(const String& _component_name) {
    component_name = _component_name;
}

String GdeComponent::get_component_name() const {
    return component_name;
}
