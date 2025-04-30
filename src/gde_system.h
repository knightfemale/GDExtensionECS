#ifndef GDE_SYSTEM_H
#define GDE_SYSTEM_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/node.hpp>

#include "gde_component.h"

namespace godot {

    class GdeSystem : public Node {
        GDCLASS(GdeSystem, Node)
        
    protected:
        static void _bind_methods();

    public:
        // 需要的组件
        Array requirements;
        void set_requirements(const Array& req);
        Array get_requirements() const;

        // 虚函数, 每帧调用
        GDVIRTUAL2(_system_process, Dictionary, double);
        // 虚函数, 每物理帧调用
        GDVIRTUAL2(_system_physics_process, Dictionary, double);
    };

}

#endif