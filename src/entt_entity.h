#ifndef ENTT_ENTITY_H
#define ENTT_ENTITY_H

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node.hpp>
#include <entt/entt.hpp>

namespace godot {

    class EnttEntity : public Node {
        GDCLASS(EnttEntity, Node);

    private:
        // entt ʵ����
        entt::entity entity;

    protected:
        static void _bind_methods();

    public:
        EnttEntity();
        ~EnttEntity();

        // entt ע����
        static entt::registry registry;
        // ��ȡʵ��
        entt::entity get_entity() const;
        void pr() const;
    };

}

#endif