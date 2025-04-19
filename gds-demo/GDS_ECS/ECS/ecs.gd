class_name ECS
extends Node


#region 静态方法
static func is_component(node: Node) -> bool:
	return "component_name" in node


static func is_system(node: Node) -> bool:
	return "system_name" in node and "requirements" in node


static func is_entity(node: Node) -> bool:
	return node.is_in_group("Entity")
#endregion
