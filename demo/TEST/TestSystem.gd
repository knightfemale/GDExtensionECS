class_name TestSystem
extends GdeSystem

func _init() -> void:
	requirements = ["!TestComponent", "GdeComponent"]
	pass


func  _system_physics_process(components: Dictionary, delta: float) -> void:
	for i in components:
		print(delta)
		pass
	pass
