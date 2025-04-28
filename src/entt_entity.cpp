#include "entt_entity.h"

using namespace godot;

entt::registry EnttEntity::registry;

void EnttEntity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_entity_id"), &EnttEntity::get_entity_id);
}

EnttEntity::EnttEntity() {
    entity = registry.create();
}

EnttEntity::~EnttEntity() {
    registry.destroy(entity);
}

entt::entity EnttEntity::get_entity() const {
    return entity;
}

uint64_t EnttEntity::get_entity_id() const {
    return static_cast<uint64_t>(entity);
}