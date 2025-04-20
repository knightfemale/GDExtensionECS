class_name RandomMotionSystem
extends System


const MAX_X = 1152
const MAX_Y = 648
const MIN_X = 0
const MIN_Y = 0
const MOVE_SPEED = 200.0
const DIRECTION_CHANGE_CHANCE = 0.3


func _init() -> void:
	requirements = ["Sprite2DComponent"]
	pass


func _system_process(entities: Array, delta: float) -> void:
	for entity in entities:
		var sprite2d_components: Array = entity.get_components("Sprite2DComponent")
		
		for sprite2d_component in sprite2d_components:
			if randf() < DIRECTION_CHANGE_CHANCE * delta:
				var random_angle = randf_range(0, TAU)
				sprite2d_component.direction = Vector2(cos(random_angle), sin(random_angle))
				pass
			
			var velocity = sprite2d_component.direction * MOVE_SPEED * delta
			var new_position = sprite2d_component.position + velocity
			
			new_position.x = clamp(new_position.x, MIN_X, MAX_X)
			new_position.y = clamp(new_position.y, MIN_Y, MAX_Y)
			
			if new_position.x == MAX_X || new_position.x == MIN_X:
				sprite2d_component.direction.x *= -1
				pass
			
			if new_position.y == MAX_Y || new_position.y == MIN_Y:
				sprite2d_component.direction.y *= -1
				pass
			
			sprite2d_component.position = new_position
			pass
		pass
	pass
