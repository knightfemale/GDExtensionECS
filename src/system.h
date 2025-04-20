#ifndef SYSTEM_H
#define SYSTEM_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>

#include "system_manager.h"

namespace godot {

    class SystemManager;

    class System : public Node {
        GDCLASS(System, Node)

    private:
        String system_name;
        SystemManager* system_manager;
        Array requirements;


    protected:
        static void _bind_methods();

    public:
        uint64_t require_mask = 0;
        uint64_t exclude_mask = 0;

        bool _system_init(SystemManager* system_manager);

        GDVIRTUAL0(_system_ready);

        GDVIRTUAL2(_system_process, Array, double);

        GDVIRTUAL2(_system_physics_process, Array, double);
        
        void set_system_name(const String& name) { system_name = name; }
        String get_system_name() const { return system_name; }

        void set_requirements(const Array& req) { requirements = req; }
        Array get_requirements() const { return requirements; }

        void precompute_requirements();
    };

}

#endif