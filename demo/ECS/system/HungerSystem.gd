class_name HungerSystem
extends System


func _init():
	system_name = "HungerSystem"
	requirements = ["HungerComponent", "HealthComponent"]


func _system_physics_process(entities: Array, delta: float) -> void:
	for e in entities:
		var hunger = e.get_component("HungerComponent")
		var health = e.get_component("HealthComponent")
		# 自动恢复
		hunger.current_hunger += hunger.recovery_rate * delta
		# 饥饿扣血
		if hunger.current_hunger < 0:
			health.current_hp -= 10 * delta
			if health.current_hp <= 0:
				e.queue_free()
				pass
			pass
		pass
	pass
