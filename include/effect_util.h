#pragma once

#include "effect_context.h"
#include "attribute_system.h"
#include "event_system.h"
#include "tag_container.h"
#include "attribute_snapshot.h"
#include "godot_cpp/classes/wrapped.hpp"
#include <godot_cpp/classes/object.hpp>
using namespace godot;

class EffectUtil : public Object {
    GDCLASS(EffectUtil, Object)

protected:
    static void _bind_methods();

public:
    static uint64_t make_combined_key(uint32_t p_key_1, uint32_t p_key_2) {
        return (static_cast<uint64_t>(p_key_1) << 32 | static_cast<uint64_t>(p_key_2));
    }

    static AttributeSystem* get_source_attributes(EffectContext* p_context);
    static AttributeSystem* get_target_attributes(EffectContext* p_context);

    static TagContainer* get_source_tag_container(EffectContext* p_context);
    static TagContainer* get_target_tag_container(EffectContext* p_context);

    static EventSystem* get_source_events(EffectContext* p_context);
    static EventSystem* get_target_events(EffectContext* p_context);

    static Ref<AttributeSnapshot> get_snapshot_for_attributes(EffectContext* p_context);

private:
    static AttributeSystem* _find_attributes(Node* p_effect_system_owner);
    static TagContainer* _find_tag_container(Node* p_effect_system_owner);
    static EventSystem* _find_events(Node* p_effect_system_owner);

};