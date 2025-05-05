extends Sprite2D


# 屏幕边界限制（根据你的需求调整）
const MAX_X = 1152
const MAX_Y = 648
const MIN_X = 0
const MIN_Y = 0
# 移动速度参数（像素/秒）
const MOVE_SPEED = 200.0

var direction : Vector2


func _init() -> void:
	var random_angle = randf_range(0, TAU)
	direction = Vector2(cos(random_angle), sin(random_angle))
	pass


func _process(delta: float) -> void:
	# 计算移动量
	var velocity = direction * MOVE_SPEED * delta
	var new_position = position + velocity
	
	# 边界限制
	new_position.x = clamp(new_position.x, MIN_X, MAX_X)
	new_position.y = clamp(new_position.y, MIN_Y, MAX_Y)
	
	# 反弹处理
	if new_position.x == MAX_X || new_position.x == MIN_X:
		direction.x *= -1
		pass
	
	if new_position.y == MAX_Y || new_position.y == MIN_Y:
		direction.y *= -1
		pass
	
	position = new_position
	pass
