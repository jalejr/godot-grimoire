extends Node

@onready var ability_system: AbilitySystem = $AbilitySystem
@onready var tag_container: TagContainer = $TagContainer

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	print("We are starting")
	await get_tree().create_timer(1.0).timeout
	
	tag_container.add_tag(Tag.STATUS_BUFF_STRENGTH)
	#ability_system.try_activate(Tag.ABILITY_ATTACK_MELEE)
	
	print(tag_container.get_tag_names())
	
	print("We did the thing")
	
	await get_tree().create_timer(6.0).timeout
	
	print(tag_container.get_tag_names())
