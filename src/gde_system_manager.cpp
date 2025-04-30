#include "gde_system_manager.h"

using namespace godot;

void GdeSystemManager::_bind_methods() {
    //
}

void GdeSystemManager::_ready() {
    systems = get_systems();
    UtilityFunctions::print(systems.size());
}

void GdeSystemManager::_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (system->has_method("_system_process")) {
            Dictionary components;
            system->call("_system_process", components, delta);
        }
    }
}

void GdeSystemManager::_physics_process(double delta) {
    for (int i = 0; i < systems.size(); ++i) {
        GdeSystem* system = Object::cast_to<GdeSystem>(systems[i]);
        if (system->has_method("_system_physics_process")) {
            Dictionary components;
            system->call("_system_physics_process", components, delta);
        }
    }
}

Array GdeSystemManager::get_systems() {
    Array result;
    Array children = get_children();
    for (int i = 0; i < children.size(); ++i) {
        if (GdeSystem* child = Object::cast_to<GdeSystem>(children[i])) {
            result.append(child);
        }
    }
    return result;
}
