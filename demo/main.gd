extends Node


var grass: PackedScene = load("res://ECS/entity/grass.tscn")
var sheep: PackedScene = load("res://ECS/entity/sheep.tscn")
var wolf: PackedScene = load("res://ECS/entity/wolf.tscn")


func _ready() -> void:
	# 生成草
	for i in 500:
		var grass_instance = grass.instantiate()
		add_child(grass_instance)
		grass_instance.add_to_group("grass")
		pass
	
	# 生成羊
	for i in 50:
		var sheep_instance = sheep.instantiate()
		add_child(sheep_instance)
		sheep_instance.add_to_group("sheep")
		pass
	
	# 生成狼
	for i in 5:
		var wolf_instance = wolf.instantiate()
		add_child(wolf_instance)
		wolf_instance.add_to_group("wolf")
		pass
	pass
