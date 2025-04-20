extends Node


var entity: PackedScene = load("res://CPP_ECS/Entity.tscn")
var component: PackedScene = load("res://CPP_ECS/Sprite2DComponent.tscn")


func _process(_delta: float) -> void:
	var temp: Entity = entity.instantiate()
	
	for i in range(10):
		temp.add_child(component.instantiate())
		pass
	
	self.add_child(temp)
	
	if self.get_child_count() >= 1000:
		print(Time.get_ticks_msec())
		set_process(false)
		pass
	pass
