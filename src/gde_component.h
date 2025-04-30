#ifndef GDE_COMPONENT_H
#define GDE_COMPONENT_H

#include "gde_entity.h"

namespace godot {

    class GdeComponent : public Node {
        GDCLASS(GdeComponent, Node);

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void _exit_tree() override;

        // 组件名称
        String component_name = "GdeComponent";
        void set_component_name(const String& _component_name);
        String get_component_name() const;
        // 缓存名称(标准字符串, 用于高效查找)
        std::string cached_component_name;

#ifndef DEBUG_DISABLED
        // 生成组件列表的辅助函数(减少代码冗余)
        String generate_components_list(GdeEntity* entity);
#endif
    };

}

#endif