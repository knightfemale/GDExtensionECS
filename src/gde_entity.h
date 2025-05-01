#ifndef GDE_ENTITY_H
#define GDE_ENTITY_H

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>

#include "gde_sparse_set.h"

namespace godot {
    class GdeComponent;

    class GdeEntity : public Node {
        GDCLASS(GdeEntity, Node);

    protected:
        static void _bind_methods();

    public:
        GdeEntity();
        ~GdeEntity();

        // 下一个可分配 ID
        static size_t next_entity_id;
        // 可复用的空闲 ID 队列
        static std::queue<size_t> free_entity_ids;
        // 活跃实体 ID
        static std::unordered_set<size_t> active_entity_ids;
        // 实体 ID 操作的互斥锁
        static std::mutex entity_id_mutex;
        // 组件操作的互斥锁
        static std::mutex component_mutex;
        // 组件类型注册表
        static std::unordered_map<std::string, int> component_type_ids;
        // 组件稀疏集存储
        static std::vector<SparseSet<GdeComponent*>> component_sparse_sets;

        // 当前实体的 ID
        size_t entity_id;

        // 实体注册组件
        void add_component(GdeComponent* component);
        // 实体注销组件
        void remove_component(const std::string& component_name);
        // 打印所有实体 ID
        static void print_entity_id_list();
        // 打印某个实体当前的组件
        static void print_components_list(GdeEntity* entity);
    };

}

#endif