extends Node


# 屏幕边界限制（根据你的需求调整）
const MAX_X = 1152
const MAX_Y = 648
const MIN_X = 0
const MIN_Y = 0

# 移动速度参数（像素/秒）
const MOVE_SPEED = 200.0
# 每秒改变方向的概率
const DIRECTION_CHANGE_CHANCE = 0.3


func _process(delta: float) -> void:
	var sprite2d = $Sprite2D
	#这里实现sprite2d.position随机游走，但position.x不超过1152,position.y不超过648
	# 添加随机方向变化
	if randf() < DIRECTION_CHANGE_CHANCE * delta:
		var random_angle = randf_range(0, TAU)
		sprite2d.direction = Vector2(cos(random_angle), sin(random_angle))
		pass
	
	# 计算移动量
	var velocity = sprite2d.direction * MOVE_SPEED * delta
	var new_position = sprite2d.position + velocity
			
	# 边界限制
	new_position.x = clamp(new_position.x, MIN_X, MAX_X)
	new_position.y = clamp(new_position.y, MIN_Y, MAX_Y)
			
	# 反弹处理（可选）
	if new_position.x == MAX_X || new_position.x == MIN_X:
		sprite2d.direction.x *= -1
		pass
	
	if new_position.y == MAX_Y || new_position.y == MIN_Y:
		sprite2d.direction.y *= -1
		pass
	
	sprite2d.position = new_position
	pass
