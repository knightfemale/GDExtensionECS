#include "entt_entity.h"
#include "entt_component.h"

using namespace godot;

entt::registry EnttEntity::registry;

void EnttEntity::_bind_methods() {
    //
    ClassDB::bind_method(D_METHOD("pr"), &EnttEntity::pr);

}

EnttEntity::EnttEntity() {
    // ����ʵ��
    entity = registry.create();

#ifndef DEBUG_DISABLED
    // ���ʵ���Ƿ���Ч
    bool is_valid = registry.valid(entity);
    // ��ȡʵ�嵱ǰ�汾
    auto version = registry.current(entity);
    UtilityFunctions::print("[EnttEntity] Added Entity ID: ", static_cast<uint32_t>(entity), " validity: ", is_valid, " version: ", version);
#endif
}

EnttEntity::~EnttEntity() {
    // ����ʵ��
    registry.destroy(entity);
}

entt::entity EnttEntity::get_entity() const {
    return entity;
}

void EnttEntity::pr() const {
    bool has = registry.all_of<EnttComponent*>(entity);
    UtilityFunctions::print(has);
}