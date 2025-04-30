#include "gde_entity.h"
#include "gde_component.h"

using namespace godot;

size_t GdeEntity::next_entity_id = 0;
std::unordered_map<std::string, int> GdeEntity::component_type_ids;
std::vector<SparseSet<GdeComponent*>> GdeEntity::component_sparse_sets;
std::queue<size_t> GdeEntity::free_entity_ids;
std::mutex GdeEntity::entity_id_mutex;
std::mutex GdeEntity::component_mutex;

void GdeEntity::_bind_methods() {
    // 预留方法绑定
}

GdeEntity::GdeEntity() {
    // 线程安全的实体 ID 分配
    std::lock_guard<std::mutex> lock(entity_id_mutex);
    if (free_entity_ids.empty()) {
        // 分配新 ID
        entity_id = next_entity_id++;
    }
    else {
        // 复用回收的 ID
        entity_id = free_entity_ids.front();
        free_entity_ids.pop();
    }

#ifndef DEBUG_DISABLED
    // 调试信息: 打印当前所有活跃实体 ID
    UtilityFunctions::print("[GdeEntity] Created entity ", entity_id, ". Current entities: ", generate_entity_id_list());
#endif
}

GdeEntity::~GdeEntity() {
    std::lock_guard<std::mutex> lock(entity_id_mutex);
    // 回收 ID
    free_entity_ids.push(entity_id);
    // 清理该实体的所有组件记录, 防止新实体复用时读到脏数据
    for (auto& sparse_set : component_sparse_sets) {
        sparse_set.remove(entity_id);
    }

#ifndef DEBUG_DISABLED
    // 调试信息: 打印当前所有活跃实体 ID
    UtilityFunctions::print("[GdeEntity] Destroyed entity ", entity_id, ". Current entities: ", generate_entity_id_list());
#endif
}

void GdeEntity::add_component(GdeComponent* component) {
    // 线程安全: 组件操作需加锁, 避免并发修改 component_type_ids 或 component_sparse_sets
    std::lock_guard<std::mutex> lock(component_mutex);
    // 直接使用组件预缓存的名称(避免实时字符串转换)
    std::string name = component->cached_component_name;

    // 组件类型注册逻辑:
    // 1. 若当前组件类型未注册, 分配唯一 type_id
    // 2. 扩展稀疏集列表以容纳新类型
    if (component_type_ids.find(name) == component_type_ids.end()) {
        // 新类型 ID 等于当前已注册类型数量
        int new_type_id = component_type_ids.size();
        // 注册映射关系(name -> type_id)
        component_type_ids[name] = new_type_id;
        // 稀疏集列表扩容(保证索引 new_type_id 有效)
        component_sparse_sets.resize(new_type_id + 1);
    }

    // 将组件插入到对应类型的稀疏集中
    // 稀疏集通过 entity_id 快速定位组件，保证 O(1) 时间复杂度
    int type_id = component_type_ids[name];
    component_sparse_sets[type_id].add(entity_id, component);
}

void GdeEntity::remove_component(const std::string& component_name) {
    // 线程安全: 组件操作需加锁, 与 add_component 共享同一锁
    std::lock_guard<std::mutex> lock(component_mutex);
    // 查找组件类型是否已注册
    auto it = component_type_ids.find(component_name);
    if (it != component_type_ids.end()) {
        int type_id = it->second;
        // 防御性检查: 确保 type_id 在稀疏集列表范围内
        if (type_id < component_sparse_sets.size()) {
            // 从稀疏集中移除该实体的组件
            component_sparse_sets[type_id].remove(entity_id);
        }
    }
}

#ifndef DEBUG_DISABLED
String GdeEntity::generate_entity_id_list() {
    std::unordered_set<size_t> free_ids;
    std::queue<size_t> temp_free = free_entity_ids;
    while (!temp_free.empty()) {
        free_ids.insert(temp_free.front());
        temp_free.pop();
    }

    String ids_list = "[";
    for (size_t id = 0; id < next_entity_id; ++id) {
        if (!free_ids.count(id)) {
            ids_list += String::num_int64(id) + ", ";
        }
    }
    if (ids_list.length() > 1) {
        ids_list = ids_list.substr(0, ids_list.length() - 2);
    }
    ids_list += "]";
    return ids_list;
}
#endif