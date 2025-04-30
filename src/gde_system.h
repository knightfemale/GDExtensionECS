#ifndef GDE_SYSTEM_H
#define GDE_SYSTEM_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>

namespace godot {

    class GdeSystem : public Node {
        GDCLASS(GdeSystem, Node)
        
    protected:
        static void _bind_methods();

    public:
        String system_name = "GdeSystem";
        void set_system_name(const String& name);
        String get_system_name() const;
        Array requirements;
        void set_requirements(const Array& req);
        Array get_requirements() const;

        GDVIRTUAL2(_system_process, Array, double);
        GDVIRTUAL2(_system_physics_process, Array, double);
    };

}

#endif