#include <godot_cpp/classes/wrapped.hpp>

#include "system.h"

using namespace godot;

void System::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_system_name", "name"), &System::set_system_name);
    ClassDB::bind_method(D_METHOD("get_system_name"), &System::get_system_name);
    ClassDB::bind_method(D_METHOD("set_requirements", "requirements"), &System::set_requirements);
    ClassDB::bind_method(D_METHOD("get_requirements"), &System::get_requirements);

    ClassDB::bind_method(D_METHOD("_system_init", "_system_manager"), &System::_system_init);
    GDVIRTUAL_BIND(_system_ready);
    GDVIRTUAL_BIND(_system_process, "entities", "delta");
    GDVIRTUAL_BIND(_system_physics_process, "entities", "delta");

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "system_name"), "set_system_name", "get_system_name");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "requirements"), "set_requirements", "get_requirements");
}

bool System::_system_init(SystemManager* _system_manager) {
    system_manager = _system_manager;
    precompute_requirements();
    return true;
}

void System::precompute_requirements() {
    Array reqs = get_requirements();
    for (int i = 0; i < reqs.size(); ++i) {
        String req = reqs[i];
        if (req.begins_with("!")) {
            String name = req.substr(1);
            exclude_mask |= ECS::get_component_bit(name);
        }
        else {
            require_mask |= ECS::get_component_bit(req);
        }
    }
}
