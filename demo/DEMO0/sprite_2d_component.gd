class_name Sprite2DComponent
extends GdeComponent


@onready var sprite2d_node: Sprite2D = $Sprite2D
var direction : Vector2


func _init() -> void:
	component_name = "Sprite2DComponent"
	var random_angle = randf_range(0, TAU)
	direction = Vector2(cos(random_angle), sin(random_angle))
	pass
