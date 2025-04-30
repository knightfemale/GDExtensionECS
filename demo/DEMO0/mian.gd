extends Node


var sprite2d_component: PackedScene = load("res://DEMO0/Sprite2DComponent.tscn")


func _process(_delta: float) -> void:
	var temp: GdeEntity = GdeEntity.new()
	
	for i in range(10):
		temp.add_child(sprite2d_component.instantiate())
		pass
	
	self.add_child(temp)
	
	if self.get_child_count() > 1000:
		print(Time.get_ticks_msec())
		set_process(false)
		pass
	pass
