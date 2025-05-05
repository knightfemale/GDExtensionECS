#include "gde_component.h"

using namespace godot;

void GdeComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_component_name", "name"), &GdeComponent::set_component_name);
    ClassDB::bind_method(D_METHOD("get_component_name"), &GdeComponent::get_component_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "component_name"), "set_component_name", "get_component_name");
}

void GdeComponent::_ready() {
    if (GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent())) {
        // 将组件注册到实体
        entity->add_component(this);
    }
    else {
        // 如果在编辑器模式, 则跳过
        if (Engine::get_singleton()->is_editor_hint()) return;
        // 非实体子节点则自动销毁，防止游离组件
        this->queue_free();
    }
}

void GdeComponent::_exit_tree() {
    if (GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent())) {
        entity->remove_component(cached_component_name);
    }
#ifndef DEBUG_DISABLED
    else {
        // 调试信息: 提示游离组件被销毁
        UtilityFunctions::print("[GdeComponent] Warning: A component ", component_name, " has been destroyed because it is not a child of entity.");
    }
#endif
}

void GdeComponent::set_component_name(const String& _component_name) {
    component_name = _component_name;
    // 缓存组件名称的 std::string 形式，避免频繁转换
    CharString cs = _component_name.utf8();
    cached_component_name = std::string(cs.get_data(), cs.length());
}

String GdeComponent::get_component_name() const {
    return component_name;
}
