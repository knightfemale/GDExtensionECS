class_name TestSystem
extends GdeSystem

func _init() -> void:
	requirements = ["TestComponent"]
	pass


func  _system_physics_process(components: Dictionary, delta: float) -> void:
	print(components.size())
	for i in components:
		print(delta)
		pass
	pass
