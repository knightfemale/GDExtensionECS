#ifndef GDE_SPARSE_SET_H
#define GDE_SPARSE_SET_H

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <string>

namespace godot {

    // 稀疏集模板，用于高效存储组件( O(1) 插入/删除/查找)
    template <typename T>
    class SparseSet {
    private:
        // 稀疏数组: entity_id -> dense 数组下标
        std::vector<size_t> sparse;
        // 密集数组: 按插入顺序存储 entity_id
        std::vector<size_t> dense;
        // 组件指针数组，与 dense 数组一一对应
        std::vector<T> components;

    public:
        // 添加组件
        void add(size_t entity_id, T component) {
            // 若 entity_id 超出当前范围, 扩展稀疏数组
            if (entity_id >= sparse.size()) {
                // 初始化为无效索引
                sparse.resize(entity_id + 1, -1);
            }
            // 将新实体添加到密集数组末尾
            dense.push_back(entity_id);
            // 存储组件指针
            components.push_back(component);
            // 更新稀疏数组, 记录新元素在密集数组中的位置
            sparse[entity_id] = dense.size() - 1;
        }

        // 获取组件
        T get(size_t entity_id) {
            // 防御性检查：
            // 1. 实体ID是否超出稀疏数组范围
            // 2. 稀疏数组中的索引是否指向有效密集数组位置
            if (entity_id >= sparse.size() || sparse[entity_id] >= dense.size()) {
                // 若不存在返回 nullptr
                return nullptr;
            }
            // 通过稀疏数组直接定位组件
            return components[sparse[entity_id]];
        }

        // 移除组件
        void remove(size_t entity_id) {
            // 有效性检查(与 get() 逻辑一致)
            if (entity_id >= sparse.size() || sparse[entity_id] >= dense.size()) {
                return;
            }
            // 获取被删除元素在密集数组中的位置
            size_t index = sparse[entity_id];
            // 将末尾元素移动到被删除位置
            components[index] = components.back();
            // // 移除末尾组件
            components.pop_back();
            // 获取最后一个entity_id
            size_t last_entity = dense.back();
            // 更新密集数组被删除位置
            dense[index] = last_entity;
            // 更新最后一个元素的稀疏索引
            sparse[last_entity] = index;
            // 移除密集数组末尾元素
            dense.pop_back();
            // 标记该entity_id为无效
            sparse[entity_id] = -1;
        }
    };

}

#endif