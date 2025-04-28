#ifndef ENTT_ENTITY_H
#define ENTT_ENTITY_H

#include <godot_cpp/classes/node.hpp>
#include <entt/entt.hpp>

namespace godot {

    class EnttEntity : public Node {
        GDCLASS(EnttEntity, Node);

    private:
        entt::entity entity;

    protected:
        static void _bind_methods();

    public:
        EnttEntity();
        ~EnttEntity();

        static entt::registry registry;
        entt::entity get_entity() const;
        uint64_t get_entity_id() const;
    };

}

#endif