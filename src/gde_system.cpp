#include <godot_cpp/classes/wrapped.hpp>

#include "gde_system.h"

using namespace godot;

void GdeSystem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_system_name", "name"), &GdeSystem::set_system_name);
    ClassDB::bind_method(D_METHOD("get_system_name"), &GdeSystem::get_system_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "system_name"), "set_system_name", "get_system_name");
    ClassDB::bind_method(D_METHOD("set_requirements", "requirements"), &GdeSystem::set_requirements);
    ClassDB::bind_method(D_METHOD("get_requirements"), &GdeSystem::get_requirements);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "requirements"), "set_requirements", "get_requirements");

    GDVIRTUAL_BIND(_system_process, "entities", "delta");
    GDVIRTUAL_BIND(_system_physics_process, "entities", "delta");
}

void GdeSystem::set_system_name(const String& name) {
    system_name = name;
}

String GdeSystem::get_system_name() const {
    return system_name;
}

void GdeSystem::set_requirements(const Array& req) {
    requirements = req;
}

Array GdeSystem::get_requirements() const {
    return requirements;
}
