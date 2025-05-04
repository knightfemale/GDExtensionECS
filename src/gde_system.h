#ifndef GDE_SYSTEM_H
#define GDE_SYSTEM_H

#include <godot_cpp/core/gdvirtual.gen.inc>

#include "gde_component.h"

namespace godot {

    class GdeSystem : public Node {
        GDCLASS(GdeSystem, Node)
        
    protected:
        static void _bind_methods();

    public:
        // 需要的组件, 形如["Component1", "!Component2", ...], 其中 "!Component3" 代表不能有 Component2
        Array requirements;
        void set_requirements(const Array& _requirements);
        Array get_requirements() const;
        // 添加缓存字段
        std::vector<std::string> cached_required;
        std::vector<std::string> cached_excluded;

        // 符合条件的实体数量
        int entity_count;
        // 符合条件的实体的相关组件
        Dictionary components_dict;

        // 虚函数, 每帧调用
        GDVIRTUAL3(_system_process, Dictionary, int, double);
        // 虚函数, 每物理帧调用
        GDVIRTUAL3(_system_physics_process, Dictionary, int, double);
    };

}

#endif