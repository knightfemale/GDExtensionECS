extends Node


func _ready() -> void:
	var gde_component = GdeComponent.new()
	var test_component = load("res://TEST/TestComponent.gd").new()
	var entity0 = GdeEntity.new()
	var entity1 = GdeEntity.new()
	
	entity0.add_child(test_component)
	entity0.add_child(gde_component)
	add_child(entity0)
	add_child(entity1)
	
	#gde_component.free()
	#entity0.free()
	#entity1.free()
	pass
