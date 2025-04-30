class_name TestComponent
extends GdeComponent


@export var test = "正常运行" 


func _init() -> void:
	component_name = "TestComponent"
	# 或者使用下面的方法
	#set_component_name("TestComponent")
	pass
