#ifndef ENTT_COMPONENT_H
#define ENTT_COMPONENT_H

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>

#include "entt_entity.h"

namespace godot {

    class EnttComponent : public Node {
        GDCLASS(EnttComponent, Node);

    protected:
        static void _bind_methods();

    private:
        String component_name = "EnttComponent";

    public:
        void set_component_name(const String& p_name);
        String get_component_name() const;

        void _ready() override;
    };

}

#endif