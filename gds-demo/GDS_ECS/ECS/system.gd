class_name System
extends Node


#region 变量
var system_name: String

var system_manager: SystemManager

var requirements: Array[String]
#endregion


#region 方法
func _system_init(_system_manager: SystemManager) -> bool:
	system_manager = _system_manager
	return true


func _system_ready() -> void:
	
	pass


func _system_process(_entities: Array[Node], _delta: float) -> void:
	
	pass


func _system_physics_process(_entities: Array[Node], _delta: float) -> void:
	
	pass
#endregion
