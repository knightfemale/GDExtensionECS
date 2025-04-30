#ifndef GDE_ENTITY_H
#define GDE_ENTITY_H

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    class GdeEntity : public Node {
        GDCLASS(GdeEntity, Node);

    protected:
        static void _bind_methods();

    public:
        GdeEntity();
        ~GdeEntity();
    };

}

#endif