class_name AttackComponent
extends Node


var component_name := "AttackComponent"
@export var damage := 10.0
# 目标类型
@export var target_type := "" # "grass"/"sheep"
@export var attack_cooldown := 1.0  # 攻击间隔（秒）
var last_attack_time := 0.0  # 上次攻击时间
@export var attack_range := 50.0  # 攻击距离
