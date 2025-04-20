#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/templates/hashfuncs.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <vector>

#include "ecs.h"
#include "entity.h"
#include "system.h"

namespace godot {

    class SystemManager : public Node {
        GDCLASS(SystemManager, Node)

    private:
        struct ComponentGroup {
            uint64_t require_mask;
            uint64_t exclude_mask;
            Array entities;
        };

        std::vector<ComponentGroup*> component_groups;
        Array systems;

    protected:
        static void _bind_methods();

    public:
        ~SystemManager();

        void _ready() override;
        void _process(double delta) override;
        void _physics_process(double delta) override;

        void _on_node_added(Node* node);
        void _on_node_removed(Node* node);
        void _on_tree_exited();

        Array get_systems();
        bool validate_system(Node* system);
        Array query_entities(Node* system);
        void register_requirements(const Array& requirements);
        void update_component_groups(Node* entity);
    };

}

#endif