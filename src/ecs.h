#ifndef ECS_H
#define ECS_H

#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    class ECS : public Node {
        GDCLASS(ECS, Node)

    protected:
        static void _bind_methods();

    private:
        static HashMap<String, uint32_t> component_bits;
        static uint32_t next_bit;

    public:
        static bool is_component(Node* node);

        static bool is_system(Node* node);
    
        static bool is_entity(Node* node);

        static uint32_t get_component_bit(const String& name);
    };

}

#endif