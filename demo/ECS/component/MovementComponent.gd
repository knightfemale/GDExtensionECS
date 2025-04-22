class_name MovementComponent
extends Sprite2D

var component_name: String = "MovementComponent"
@onready var body: Area2D = $Body
@onready var vision: Area2D = $Vision
# 方向
@export var current_direction: Vector2
# 速度
@export var speed = 30

# 是否随机生成
@export var is_random_generation = true


func _ready() -> void:
	if is_random_generation:
		self.position = Vector2(randf_range(0.0, 1920.0), randf_range(0.0, 1080.0))
		pass
	pass
