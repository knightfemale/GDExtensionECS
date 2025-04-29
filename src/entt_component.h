#ifndef ENTT_COMPONENT_H
#define ENTT_COMPONENT_H

#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>

#include "entt_entity.h"

namespace godot {

    class EnttComponent : public Node {
        GDCLASS(EnttComponent, Node);

    private:
        entt::entity entity;
        
    protected:
        static void _bind_methods();

    public:
        EnttComponent();
        ~EnttComponent();

        String component_name = "EnttComponent";
        void _ready() override;
        void set_component_name(const String& _component_name);
        String get_component_name() const;
    };

}

#endif