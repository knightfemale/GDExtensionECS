class_name HungerComponent
extends Node


var component_name := "HungerComponent"
# 当前饱腹
@export var current_hunger: float
# 每秒恢复量
@export var recovery_rate: float


func _ready() -> void:
	current_hunger = randi_range(10, 30)
	pass
