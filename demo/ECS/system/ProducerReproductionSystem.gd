class_name ProducerReproductionSystem
extends System


var grass: PackedScene = load("res://ECS/entity/grass.tscn")


func _init():
	system_name = "ProducerReproductionSystem"
	requirements = ["HungerComponent", "!AttackComponent"]
	pass


func _system_process(entities, _delta):
	for e in entities:
		var hunger = e.get_component("HungerComponent")
		
		if hunger.current_hunger >= 100.0:
			var grass_instance = grass.instantiate()
			grass_instance.add_to_group("grass")
			add_child(grass_instance)
			hunger.current_hunger = 0.0
			pass
		pass
	pass
