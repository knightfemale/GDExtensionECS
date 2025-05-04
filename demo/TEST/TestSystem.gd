class_name TestSystem
extends GdeSystem

func _init() -> void:
	set_requirements(["TestComponent", "GdeComponent"])
	pass


func  _system_physics_process(components: Dictionary, count: int, _delta: float) -> void:
	var test_components = components["TestComponent"]
	
	for i in count:
		var current_test_component = test_components[i]
		print(current_test_component.test)
		pass
	pass
