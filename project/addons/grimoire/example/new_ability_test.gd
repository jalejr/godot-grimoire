extends AbilityLogic

func _can_commit() -> bool:
	return true

func _on_commit() -> void:
	print("we commit")

func _on_activate() -> void:
	print("eeey")
	
	await get_tree().create_timer(5.0).timeout 
	
	end()

func _on_end() -> void:
	print("We ended in this")

func _on_cancel(reason: StringName) -> void:
	print(reason)
