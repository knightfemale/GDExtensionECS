#ifndef ECS_H
#define ECS_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

    class ECS : public Node {
        GDCLASS(ECS, Node)

    protected:
        static void _bind_methods();

    public:
        static bool is_component(Node* node);

        static bool is_system(Node* node);
    
        static bool is_entity(Node* node);
    };

}

#endif