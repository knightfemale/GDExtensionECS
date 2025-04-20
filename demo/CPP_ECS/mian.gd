extends Node


var entity = load("res://CPP_ECS/Entity.tscn")
var component = load("res://CPP_ECS/Sprite2DComponent.tscn")


func _physics_process(_delta: float) -> void:
	var temp = entity.instantiate()
	
	for i in range(10):
		temp.add_child(component.instantiate())
	
	self.add_child(temp)
	
	if self.get_child_count() >= 1000:
		print(Time.get_ticks_msec())
		set_physics_process(false)
		pass
	pass
