#ifndef ENTITY_H
#define ENTITY_H

#include <godot_cpp/classes/node.hpp>

#include "ecs.h"

namespace godot {

    class Entity : public Node {
        GDCLASS(Entity, Node)

    private:
        uint64_t component_bitmask = 0;
        Array components;

    protected:
        static void _bind_methods();

    public:
        int get_id() const { return get_instance_id(); }

        void _ready() override;
        void register_component(Node* component);
        void unregister_component(Node* component);
        Node* get_component(const String& component_name) const;
        Array get_components(const String& component_name) const;
        uint64_t get_component_bitmask() const { return component_bitmask; }
    };

}

#endif