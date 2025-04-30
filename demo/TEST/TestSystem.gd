class_name TestSystem
extends GdeSystem

func _init() -> void:
	requirements = ["TestComponent", "!GdeComponent"]
	pass


func  _system_physics_process(components: Dictionary, delta: float) -> void:
	var test_component = components["TestComponent"]
	for i in test_component.size():
		var current_test_component = test_component[i]
		print(current_test_component.test)
		pass
	pass
