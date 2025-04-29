#ifndef ENTT_ENTITY_H
#define ENTT_ENTITY_H

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node.hpp>
#include <entt/entt.hpp>

namespace godot {

    class EnttEntity : public Node {
        GDCLASS(EnttEntity, Node);

    private:
        // entt 实体类
        entt::entity entity;

    protected:
        static void _bind_methods();

    public:
        EnttEntity();
        ~EnttEntity();

        // entt 注册类
        static entt::registry registry;
        // 获取实体
        entt::entity get_entity() const;
        void pr() const;
    };

}

#endif