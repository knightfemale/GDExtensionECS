class_name SystemManager 
extends Node


#region 变量
# 形如 {["HealthComponent", "MagicComponent"]: [Entity1, Entity2], ["HealthComponent"]: [Entity1, Entity2, Entity3]}
var component_groups: Dictionary

var systems: Array[System]
#endregion


#region 内置方法
func _ready() -> void:
	var scene_tree: SceneTree = get_tree()
	
	scene_tree.node_added.connect(_on_node_added)
	scene_tree.node_removed.connect(_on_node_removed)
	tree_exited.connect(_on_scene_tree_exited)
	systems = get_systems()
	
	for node in get_children():
		if ECS.is_system(node):
			register_requirements(node.requirements)
			pass
		pass
	
	# 遍历场景树中现有的所有实体并更新组件组字典
	for entity in get_tree().get_nodes_in_group("Entity"):
		update_component_groups(entity)
		pass
	
	for node in get_children():
		if ECS.is_system(node) and "system_name" in node:
			node._system_ready()
			pass
		pass
	pass


func _process(delta: float) -> void:
	for system in get_children():
		if ECS.is_system(system) and system.has_method("_system_process"):
			system.call("_system_process", query_entities(system), delta)
			pass 
		pass
	pass


func _physics_process(delta: float) -> void:
	for system in get_children():
		if ECS.is_system(system) and system.has_method("_system_physics_process"):
			system.call("_system_physics_process", query_entities(system), delta)
			pass 
		pass
	pass
#endregion


#region 方法
func _on_node_added(node: Node) -> void:
	if ECS.is_component(node):
		var entity: Node = node.get_parent()
		
		entity.register_component(node)
		update_component_groups(entity)
	elif ECS.is_entity(node):
		update_component_groups(node)
		pass
	pass


func _on_node_removed(node: Node) -> void:
	if ECS.is_component(node):
		var entity: Node = node.get_parent()
		
		entity.unregister_component(node)
		update_component_groups(entity)
	elif ECS.is_entity(node):
		update_component_groups(node)
		pass
	pass 


func _on_scene_tree_exited() -> void:
	var scene_tree: SceneTree = get_tree()
	
	if not scene_tree: return # 防止游戏退出时报错的卫语句
	
	scene_tree.node_added.disconnect(_on_node_added)
	scene_tree.node_removed.disconnect(_on_node_removed)
	pass


func get_systems() -> Array[System]:
	var results: Array[System]
	
	for node in get_children():
		if ECS.is_system(node):
			if Engine.is_editor_hint():
				results.append(node)
			elif validate_system(node):
				results.append(node)
				pass
			pass
		pass
	
	return results


func validate_system(system: System) -> bool:
	if not system.has_method("_system_init"):
		push_error("[System: %s] 没有 _system_init() 方法" % system.system_name)
		return false
	if not system.call("_system_init", self):
		push_error("[System: %s] 的 _system_init() 方法返回 false" % system.system_name)
		return false
	if system.requirements.is_empty():
		push_error("[System: %s] 尝试在没有要求的情况下注册" % system.system_name)
		return false
	
	return true


func query_entities(system: System) -> Array[Node]:
	return component_groups.get(system.requirements, [])


func register_requirements(requirements: Array[String]):
	# 排序防止因顺序不同被判定为不同的要求
	requirements.sort()
	
	# 组件组只是系统所需的不同组件的组
	if not requirements in component_groups:
		var entities: Array[Node]
		
		component_groups[requirements] = entities
		pass
	pass


func update_component_groups(entity: Node) -> void:
	for component_group in component_groups:
		var entity_list: Array[Node] = component_groups[component_group]
		if entity.meet_requirements(component_group):
			if not entity in entity_list:
				entity_list.append(entity)
				pass
		else:
			entity_list.erase(entity)
			pass
		pass
	pass
#endregion
