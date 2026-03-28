#pragma once

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/object.hpp"
#include "godot_cpp/classes/wrapped.hpp"

using namespace godot;

class AbilitySystem;
class AttributeSystem;
class EffectSystem;
class TagContainer;
class EventSystem;

class AbilityUtil : public Object {
    GDCLASS(AbilityUtil, Object)

protected:
    static void _bind_methods();

public:
    static Node* get_owner(AbilitySystem* p_system);
    static AttributeSystem* get_attributes(AbilitySystem* p_system);
    static EffectSystem* get_effects(AbilitySystem* p_system);
    static TagContainer* get_tags(AbilitySystem* p_system);
    static EventSystem* get_events(AbilitySystem* p_system);
};