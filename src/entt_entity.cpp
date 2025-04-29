#include "entt_entity.h"
#include "entt_component.h"

using namespace godot;

entt::registry EnttEntity::registry;

void EnttEntity::_bind_methods() {
    //
    ClassDB::bind_method(D_METHOD("pr"), &EnttEntity::pr);

}

EnttEntity::EnttEntity() {
    // 创建实体
    entity = registry.create();

#ifndef DEBUG_DISABLED
    // 检查实体是否有效
    bool is_valid = registry.valid(entity);
    // 获取实体当前版本
    auto version = registry.current(entity);
    UtilityFunctions::print("[EnttEntity] Added Entity ID: ", static_cast<uint32_t>(entity), " validity: ", is_valid, " version: ", version);
#endif
}

EnttEntity::~EnttEntity() {
    // 销毁实体
    registry.destroy(entity);
}

entt::entity EnttEntity::get_entity() const {
    return entity;
}

void EnttEntity::pr() const {
    bool has = registry.all_of<EnttComponent*>(entity);
    UtilityFunctions::print(has);
}