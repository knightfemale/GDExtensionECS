extends Node


var entity: GdeEntity = GdeEntity.new()
var sprite2d_component: PackedScene = load("res://DEMO0/Sprite2DComponent.tscn")


func _init() -> void:
	entity.add_child(sprite2d_component.instantiate())
	pass


func _process(_delta: float) -> void:
	var temp: GdeEntity = entity.duplicate()
	self.add_child(temp)
	#GdeEntity.print_components_list(temp)
	
	if self.get_child_count() > 10000:
		print(Time.get_ticks_msec())
		#GdeEntity.print_entity_id_list()
		set_process(false)
		pass
	pass
