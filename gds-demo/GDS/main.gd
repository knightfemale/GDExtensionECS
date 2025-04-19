extends Node

func _ready() -> void:
	var entity = load("res://GDS/Object.tscn")
	
	for i in range(pow(2, 14)):
		add_child(entity.instantiate())
		pass
	pass
