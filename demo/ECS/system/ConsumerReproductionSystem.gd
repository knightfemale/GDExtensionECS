class_name ConsumerReproductionSystem
extends System


func _init():
	system_name = "ConsumerReproductionSystem"
	requirements = ["MovementComponent", "HungerComponent", "GenderComponent"]
	pass


func _system_process(entities, _delta):
	for e in entities:
		var mov = e.get_component("MovementComponent")
		var hunger = e.get_component("HungerComponent")
		var gender = e.get_component("GenderComponent")
		
		if hunger.current_hunger >= 100.0:
			var subclass = load("res://ECS/entity/" + gender.subclass_name + ".tscn")
			var subclass_instance = subclass.instantiate()
			subclass_instance.get_child(0).is_random_generation = false
			subclass_instance.get_child(0).position = mov.position + Vector2(randf_range(-64.0, 64.0), randf_range(-64.0, 64.0))
			subclass_instance.add_to_group(gender.subclass_name)
			get_parent().get_parent().add_child(subclass_instance)
			hunger.current_hunger = 50
			pass
		pass
	pass
