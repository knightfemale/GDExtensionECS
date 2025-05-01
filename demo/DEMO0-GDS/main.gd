extends Node


var sprite2d_component: PackedScene = load("res://DEMO0-GDS/sprite_2d.tscn")


func _process(_delta: float) -> void:
	add_child(sprite2d_component.instantiate())
	
	if self.get_child_count() > 10000:
		print(Time.get_ticks_msec())
		set_process(false)
		pass
	pass
