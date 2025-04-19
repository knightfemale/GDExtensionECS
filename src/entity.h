#ifndef ENTITY_H
#define ENTITY_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

    class Entity : public Node {
        GDCLASS(Entity, Node)

    private:
        Array components;

    protected:
        static void _bind_methods();

    public:
        int get_id() const { return get_instance_id(); }

        void _ready() override;
        void register_component(Node* component);
        void unregister_component(Node* component);
        void _on_child_added(Node* node);
        Node* get_component(const String& component_name) const;
        Array get_components(const String& component_name) const;
        bool meets_requirements(const Array& requirements) const;
    };

}

#endif