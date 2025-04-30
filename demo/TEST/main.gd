extends Node


func _ready() -> void:
	var entt_component = GdeComponent.new()
	var test_component = load("res://TEST/TestComponent.gd").new()
	var entt_entity = GdeEntity.new()
	var entt_entity2 = GdeEntity.new()
	
	entt_entity.add_child(entt_component)
	entt_entity.add_child(test_component)
	add_child(entt_entity)
	add_child(entt_entity2)
	
	entt_component.queue_free()
	entt_entity.queue_free()
	entt_entity2.queue_free()
	pass
