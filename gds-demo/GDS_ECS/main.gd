extends Node

func _ready() -> void:
	var entity = load("res://GDS_ECS/Entity.tscn")
	var component = load("res://GDS_ECS/Sprite2DComponent.tscn")
	
	for i in range(pow(2, 14)):
		var temp = entity.instantiate()
		temp.add_child(component.instantiate())
		add_child(temp)
		pass
	pass
