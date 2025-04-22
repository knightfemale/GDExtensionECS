class_name AnimalAISystem
extends System


func _init():
	system_name = "AnimalAISystem"
	requirements = ["MovementComponent", "HungerComponent", "AttackComponent"]
	pass


func _system_process(entities, delta):
	for e in entities:
		var mov = e.get_component("MovementComponent")
		var hunger = e.get_component("HungerComponent")
		var attack = e.get_component("AttackComponent")
		
		var target_entity = null
		# 检测目标逻辑
		for target_body in mov.vision.get_overlapping_areas():
			var _target_mov = target_body.get_parent()
			var _target_entity = _target_mov.get_parent()
			if _target_entity.is_in_group(attack.target_type):
				target_entity = _target_entity
				break
			pass
		
		# 有目标时的逻辑
		if target_entity and is_instance_valid(target_entity):
			var target_mov = target_entity.get_component("MovementComponent")
			var to_target = target_mov.position - mov.position
			var distance = to_target.length()
			
			# 持续面向目标
			mov.current_direction = to_target.normalized()
			
			if distance > attack.attack_range:
				# 在攻击范围外，继续移动
				mov.position += mov.current_direction * mov.speed * delta
				hunger.current_hunger -= delta * 1
			else:
				# 进入攻击范围，停止移动专注攻击
				try_attack(hunger, attack, target_entity, delta)
				pass
		else:
			# 无目标时的随机移动
			if randf() < 0.003:
				mov.current_direction = Vector2(
					randf_range(-1, 1), 
					randf_range(-1, 1)
				).normalized()
				pass
			mov.position += mov.current_direction * mov.speed * delta
			hunger.current_hunger -= delta * 1
			pass
		pass
	pass


func try_attack(hunger, attack, target_entity, delta):
	attack.last_attack_time += delta
	
	if attack.last_attack_time >= attack.attack_cooldown:
		var target_health = target_entity.get_component("HealthComponent")
		if target_health:
			# 造成伤害
			target_health.current_hp -= attack.damage
			
			# 击杀处理
			if target_health.current_hp <= 0.0:
				transfer_hunger(hunger, target_entity)
				
				target_entity.queue_free()
				
			attack.last_attack_time = 0.0


func transfer_hunger(hunger, target_entity):
	var target_hunger = target_entity.get_component("HungerComponent")
	
	if hunger and target_hunger:
		# 转移目标剩余饱腹值的30%
		hunger.current_hunger += target_hunger.current_hunger * 0.3
