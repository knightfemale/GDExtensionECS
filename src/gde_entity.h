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

        // ��̬ vector �洢����ʵ��ʵ��
        static std::vector<GdeEntity*> entities;
        // �洢����� unordered_map
        std::unordered_map<std::string, GdeComponent*> components;
        // �������� unordered_map
        void add_component(GdeComponent* component);

        // ��¶����: �������ƴ� unordered_map ��ȡ���
        GdeComponent* get_component(const String& component_name) const;
    };

}

#endif