#ifndef GDE_ENTITY_H
#define GDE_ENTITY_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/node.hpp>

namespace godot {
    class GdeComponent;

    class GdeEntity : public Node {
        GDCLASS(GdeEntity, Node);

    protected:
        static void _bind_methods();

    public:
        GdeEntity();
        ~GdeEntity();

        // 静态 vector 存储所有实体实例
        static std::vector<GdeEntity*> entities;
        // 存储组件的 unordered_map
        std::unordered_map<std::string, GdeComponent*> components;
        // 添加组件到 unordered_map
        void add_component(GdeComponent* component);

        // 暴露函数: 根据名称从 unordered_map 获取组件
        GdeComponent* get_component(const String& component_name) const;
    };

}

#endif