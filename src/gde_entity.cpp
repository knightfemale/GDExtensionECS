#include "gde_entity.h"
#include "gde_component.h"

using namespace godot;

std::mutex GdeEntity::entities_mutex;
std::vector<GdeEntity*> GdeEntity::entities;

void GdeEntity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_component", "component_name"), &GdeEntity::get_component);
}

GdeEntity::GdeEntity() {
    // ����߳���
    std::lock_guard<std::mutex> lock(entities_mutex);
    // ����ʱ����ǰʵ������ vector
    entities.push_back(this);

#ifndef DEBUG_DISABLED
    String entities_str = "[GDExtensionECS] Current entities: [ ";
    for (GdeEntity* entity : entities) {
        entities_str += String::num_int64(entity->get_instance_id()) + ", ";
    }if (!entities.empty()) {
        entities_str = entities_str.substr(0, entities_str.length() - 2); // �Ƴ�ĩβ��", "
    }
    entities_str += "]";
    UtilityFunctions::print(entities_str);
#endif
}

GdeEntity::~GdeEntity() {
    // ����߳���
    std::lock_guard<std::mutex> lock(entities_mutex);
    // ����ʱ�� vector ���Ƴ���ǰʵ��
    auto end = std::remove(entities.begin(), entities.end(), this);
    entities.erase(end, entities.end());

#ifndef DEBUG_DISABLED
    String entities_str = "[GDExtensionECS] Current entities: [";
    for (GdeEntity* entity : entities) {
        entities_str += String::num_int64(entity->get_instance_id()) + ", ";
    }if (!entities.empty()) {
        entities_str = entities_str.substr(0, entities_str.length() - 2); // �Ƴ�ĩβ��", "
    }
    entities_str += "]";
    UtilityFunctions::print(entities_str);
#endif
}

void GdeEntity::add_component(GdeComponent* component) {
    components[component->cached_component_name] = component;
}

GdeComponent* GdeEntity::get_component(const String& component_name) const {
    CharString cs = component_name.utf8();
    std::string name(cs.get_data(), cs.length());
    auto it = components.find(name);
    return (it != components.end()) ? it->second : nullptr;
}