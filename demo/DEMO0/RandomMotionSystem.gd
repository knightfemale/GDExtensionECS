class_name RandomMotionSystem
extends GdeSystem

func _init() -> void:
	requirements = ["Sprite2DComponent"]
	pass

# 屏幕边界限制（根据你的需求调整）
const MAX_X = 1152
const MAX_Y = 648
const MIN_X = 0
const MIN_Y = 0

# 移动速度参数（像素/秒）
const MOVE_SPEED = 200.0
# 每秒改变方向的概率
const DIRECTION_CHANGE_CHANCE = 0.3


func _system_process(components: Dictionary, delta: float) -> void:
	var sprite2d_component = components["Sprite2DComponent"]
	for i in sprite2d_component.size():
		var current_sprite2d_component = sprite2d_component[i]
		var sprite2d_node = current_sprite2d_component.sprite2d_node
		#这里实现sprite2d_component.position随机游走，但position.x不超过1152,position.y不超过648
		# 计算移动量
		var velocity = current_sprite2d_component.direction * MOVE_SPEED * delta
		var new_position = sprite2d_node.position + velocity
		
		# 边界限制
		new_position.x = clamp(new_position.x, MIN_X, MAX_X)
		new_position.y = clamp(new_position.y, MIN_Y, MAX_Y)
		
		# 反弹处理
		if new_position.x == MAX_X || new_position.x == MIN_X:
			current_sprite2d_component.direction.x *= -1
		
		if new_position.y == MAX_Y || new_position.y == MIN_Y:
			current_sprite2d_component.direction.y *= -1
		
		sprite2d_node.position = new_position
		pass
	pass
