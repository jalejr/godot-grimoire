#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "tag_manager.h"
#include "tag_container.h"
#include "tag_database.h"

#include "effect_definition.h"
#include "effect_modifier.h"
#include "effect_context.h"
#include "effect_system.h"
#include "snapshot_data.h"

#include "event_system.h"

#include "attribute_definition.h"
#include "attribute_set.h"
#include "attribute_handle.h"
#include "attribute_constraint.h"
#include "reactive_state.h"
#include "attribute_system.h"

#include "ability_definition.h"
#include "ability_logic.h"
#include "ability_activation_watcher.h"
#include "ability_instance_watcher.h"
#include "ability_system.h"

#include "ability_util.h"
#include "effect_util.h"
#include "attribute_mod.h"
#include "attribute_snapshot.h"

using namespace godot;

static TagManager* tag_manager_singleton = nullptr;

void initialize_gdextension_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<TagManager>();
	tag_manager_singleton = memnew(TagManager);
	Engine::get_singleton()->register_singleton("TagManager", TagManager::get_singleton());
	
	GDREGISTER_CLASS(TagContainer)
	GDREGISTER_CLASS(TagDatabase)

	GDREGISTER_CLASS(EffectDefinition);
	GDREGISTER_CLASS(EffectModifier);
	GDREGISTER_CLASS(EffectContext);
	GDREGISTER_CLASS(EffectSystem);
	GDREGISTER_CLASS(SnapshotData);

	GDREGISTER_CLASS(EventSystem)

	GDREGISTER_CLASS(AttributeDefinition);
	GDREGISTER_CLASS(AttributeSet);
	GDREGISTER_CLASS(AttributeHandle);
	GDREGISTER_CLASS(AttributeConstraint);
	GDREGISTER_CLASS(ReactiveState);
	GDREGISTER_CLASS(AttributeSystem);
	
	GDREGISTER_CLASS(AbilityLogic)
	GDREGISTER_CLASS(AbilityDefinition)
	GDREGISTER_INTERNAL_CLASS(AbilityActivationWatcher)
	GDREGISTER_INTERNAL_CLASS(AbilityInstanceWatcher)
	GDREGISTER_CLASS(AbilitySystem)
	
	GDREGISTER_CLASS(AbilityUtil)
	GDREGISTER_CLASS(EffectUtil);
	GDREGISTER_CLASS(AttributeMod);
	GDREGISTER_CLASS(AttributeSnapshot);
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	Engine::get_singleton()->unregister_singleton("TagManager");
	memdelete(tag_manager_singleton);
	tag_manager_singleton = nullptr;
}

extern "C"
{
	// Initialization
	GDExtensionBool GDE_EXPORT grimoire_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}