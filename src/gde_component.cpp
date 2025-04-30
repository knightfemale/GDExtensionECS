#include "gde_component.h"

using namespace godot;

void GdeComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_component_name", "name"), &GdeComponent::set_component_name);
    ClassDB::bind_method(D_METHOD("get_component_name"), &GdeComponent::get_component_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "component_name"), "set_component_name", "get_component_name");
}

void GdeComponent::_ready() {
    if (GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent())) {
        // 缓存组件名称的 std::string 形式，避免频繁转换
        CharString cs = component_name.utf8();
        cached_component_name = std::string(cs.get_data(), cs.length());
        // 将组件注册到实体
        entity->add_component(this);
#ifndef DEBUG_DISABLED
        // 调试信息: 打印组件列表
        UtilityFunctions::print("[GdeComponent] Created entity: ", entity->entity_id, " a ", component_name, ". Current components: ", generate_components_list(entity));
#endif
    }
    else {
        // 非实体子节点则自动销毁，防止游离组件
        this->queue_free();
#ifndef DEBUG_DISABLED
        // 调试信息: 提示销毁游离组件
        UtilityFunctions::print("[GdeComponent] Warning: A component ", component_name, " has been destroyed because it is not a child of entity.");
#endif
    }
}

void GdeComponent::_exit_tree() {
    GdeEntity* entity = Object::cast_to<GdeEntity>(get_parent());
    entity->remove_component(cached_component_name);
#ifndef DEBUG_DISABLED
    // 调试信息: 打印组件列表
    UtilityFunctions::print("[GdeComponent] Destroyed entity: ", entity->entity_id, " a ", component_name, ". Current components: ", generate_components_list(entity));
#endif
}

void GdeComponent::set_component_name(const String& _component_name) {
    component_name = _component_name;
}

String GdeComponent::get_component_name() const {
    return component_name;
}

#ifndef DEBUG_DISABLED
String GdeComponent::generate_components_list(GdeEntity* entity) {
    String components_list = "[";
    std::lock_guard<std::mutex> lock(GdeEntity::component_mutex);
    for (const auto& pair : GdeEntity::component_type_ids) {
        int type_id = pair.second;
        if (type_id < GdeEntity::component_sparse_sets.size() &&
            GdeEntity::component_sparse_sets[type_id].get(entity->entity_id)) {
            components_list += String(pair.first.c_str()) + ", ";
        }
    }
    if (components_list.length() > 1) {
        components_list = components_list.substr(0, components_list.length() - 2);
    }
    components_list += "]";
    return components_list;
}
#endif