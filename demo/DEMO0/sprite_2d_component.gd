class_name Sprite2DComponent
extends GdeComponent


@onready var sprite2d_node: Sprite2D = $Sprite2D
var direction := Vector2.RIGHT


func _init() -> void:
	component_name = "Sprite2DComponent"
	pass
