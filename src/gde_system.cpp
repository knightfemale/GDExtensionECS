#include "gde_system.h"

using namespace godot;

void GdeSystem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_requirements", "_requirements"), &GdeSystem::set_requirements);
    ClassDB::bind_method(D_METHOD("get_requirements"), &GdeSystem::get_requirements);
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "requirements"), "set_requirements", "get_requirements");

    GDVIRTUAL_BIND(_system_process, "components", "count", "delta");
    GDVIRTUAL_BIND(_system_physics_process, "components", "count", "delta");
}

void GdeSystem::set_requirements(const Array& _requirements) {
    requirements = _requirements;

    // 清空旧缓存
    cached_required.clear();
    cached_excluded.clear();

    // 预处理组件名称到缓存
    for (int i = 0; i < requirements.size(); ++i) {
        String req = requirements[i];
        if (req.begins_with("!")) {
            CharString cs = req.substr(1).utf8();
            cached_excluded.emplace_back(cs.get_data());
        }
        else {
            CharString cs = req.utf8();
            cached_required.emplace_back(cs.get_data());
        }
    }
}

Array GdeSystem::get_requirements() const {
    return requirements;
}
