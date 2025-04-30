#include "gde_system.h"

using namespace godot;

void GdeSystem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_requirements", "requirements"), &GdeSystem::set_requirements);
    ClassDB::bind_method(D_METHOD("get_requirements"), &GdeSystem::get_requirements);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "requirements"), "set_requirements", "get_requirements");

    GDVIRTUAL_BIND(_system_process, "components", "delta");
    GDVIRTUAL_BIND(_system_physics_process, "components", "delta");
}

void GdeSystem::set_requirements(const Array& _requirements) {
    requirements = _requirements;
}

Array GdeSystem::get_requirements() const {
    return requirements;
}
