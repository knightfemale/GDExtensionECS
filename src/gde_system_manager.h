#ifndef GDE_SYSTEM_MANAGER_H
#define GDE_SYSTEM_MANAGER_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/hashfuncs.hpp>

#include "gde_system.h"

namespace godot {

    class GdeSystemManager : public Node {
        GDCLASS(GdeSystemManager, Node)
        
    protected:
        static void _bind_methods();

    public:
        Array systems;

        void _ready() override;
        void _process(double delta) override;
        void _physics_process(double delta) override;

        Array get_systems();
    };

}

#endif