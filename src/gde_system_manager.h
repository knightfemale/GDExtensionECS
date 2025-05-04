#ifndef GDE_SYSTEM_MANAGER_H
#define GDE_SYSTEM_MANAGER_H

#include "gde_system.h"

namespace godot {

    class GdeSystemManager : public Node {
        GDCLASS(GdeSystemManager, Node)

    protected:
        static void _bind_methods();

    public:
        Array systems;

        static std::mutex components_dirty_mutex;
        static bool components_dirty;
        static void mark_components_dirty();

        void _ready() override;
        void _process(double delta) override;
        void _physics_process(double delta) override;

        Array get_systems();
        void update_components(GdeSystem* system);
    };

}

#endif