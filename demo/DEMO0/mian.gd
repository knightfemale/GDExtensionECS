extends Node


var sprite2d_component: PackedScene = load("res://DEMO0/Sprite2DComponent.tscn")


func _process(_delta: float) -> void:
	var temp: GdeEntity = GdeEntity.new()
	
	temp.add_child(sprite2d_component.instantiate())
	
	self.add_child(temp)
	#GdeEntity.print_components_list(temp)
	
	if self.get_child_count() > 10000:
		print(Time.get_ticks_msec())
		#GdeEntity.print_entity_id_list()
		set_process(false)
		pass
	pass
