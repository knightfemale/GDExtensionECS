class_name Entity
extends Node


#region 变量
var ID: int:
	set(velue): pass
	get: return self.get_instance_id()

var components: Array[Node]
#endregion


#region 内置方法
func _ready() -> void:
	self.add_to_group("Entity")
	set_process(false)
	set_physics_process(false)
	set_process_input(false)
	
	for 子节点 in get_children():
		register_component(子节点)
		pass
	
	# 监听后续添加的子节点
	child_entered_tree.connect(_on_child_added)
	pass
#endregion


#region 方法
func register_component(component: Node) -> void:
	if not component in components:
		components.append(component)
		pass
	pass


func unregister_component(component: Node) -> void:
	components.erase(component)
	pass


func _on_child_added(node: Node) -> void:
	if ECS.is_component(node):
		node.name = node.component_name
		pass
	pass


func get_component(component_name: String) -> Node:
	for component in components:
		if component.component_name == component_name:
			return component
		pass
	
	return null


func get_components(component_name: String) -> Array[Node]:
	var results: Array[Node]
	for component in components:
		if component.component_name == component_name:
			results.append(component)
		pass
	
	return results


## 查询此实体是否满足所提供的一个包含组件名称的字符串数组, 前缀为 "!" 用于否定, 例如 ["HealthComponent", "!MagicComponent"]
func meet_requirements(component_group: Array[String]) -> bool:
	var matching_requirements: int = 0
	
	for component in components:
		if "!%s" % component.component_name in component_group:
			return false
		if component.component_name in component_group:
			matching_requirements += 1
			pass
		pass
	
	return matching_requirements >= component_group.size()
#endregion
