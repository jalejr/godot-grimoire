#include "attribute_mod.h"
#include "attribute_instance.h"
#include "attribute_system.h"
#include "attribute_types.h"
#include "dependency_tracker.h"
#include "effect_util.h"
#include "godot_cpp/core/error_macros.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "reactive_state.h"

using namespace godot;

void AttributeMod::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_target_attribute_tag"),
        &AttributeMod::get_target_attribute_tag);
    ClassDB::bind_method(D_METHOD("set_target_attribute_tag", "tag"),
        &AttributeMod::set_target_attribute_tag);
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "target_attribute_tag",
        PROPERTY_HINT_PLACEHOLDER_TEXT, "tag"),
        "set_target_attribute_tag", "get_target_attribute_tag");
 
    ClassDB::bind_method(D_METHOD("get_operation"),
        &AttributeMod::get_operation);
    ClassDB::bind_method(D_METHOD("set_operation", "operation"),
        &AttributeMod::set_operation);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "operation",
        PROPERTY_HINT_ENUM, "Add,Multiply,Override"),
        "set_operation", "get_operation");
 
    ClassDB::bind_method(D_METHOD("compute", "context"),
        &AttributeMod::compute);
 
    // Bound so callable_mp can form a valid Callable for reactive wiring.
    ClassDB::bind_method(D_METHOD("_reevaluate", "context", "modifier_index"),
        &AttributeMod::_reevaluate);
 
    GDVIRTUAL_BIND(_compute, "context")
}

void AttributeMod::apply(const Ref<EffectContext>& p_context) {
    AttributeSystem* attributes = EffectUtil::get_target_attributes(p_context.ptr());

    ERR_FAIL_COND_MSG(
        !attributes, 
        "AttributeMod::apply: no AttributeSystem found on target."
    );

    AttributeInstance* attribute_instance = attributes->get_instance(_target_attribute_tag);

    if (!attribute_instance) return;

    if (p_context->get_effect_id() == 0) {
        float value = compute(p_context);

        switch(_operation) {
            case Attribute::ADD:
                attribute_instance->base += value;
                break;
            case Attribute::MULTIPLY:
                attribute_instance->base *= value;
                break;
            case Attribute::OVERRIDE:
                attribute_instance->base = value;
                break;
        }

        attribute_instance->mark_dirty();
        return;
    }

    uint64_t key = EffectUtil::make_combined_key(
        static_cast<uint32_t>(p_context->get_effect_id()),
        static_cast<uint32_t>(p_context->get_modifier_index())
    );

    Ref<ReactiveState> state;
    state.instantiate();
    state->set_callable(
        callable_mp(this, &AttributeMod::_reevaluate)
        .bind(p_context, p_context->get_modifier_index())
    );

    float value = 0.0f;
    {
        TrackerScope scope(state.ptr(), attribute_instance);
        value = compute(p_context);
    }

    if (state->has_dependencies()) {
        state->connect();
        p_context->set_data(state);
    }

    attribute_instance->push_modifier(key, _operation, value);
}

void AttributeMod::remove(const Ref<EffectContext>& p_context) {
    if (p_context->get_effect_id() == 0) return;

    AttributeSystem* attributes = EffectUtil::get_target_attributes(p_context.ptr());

    if (!attributes) return;
    
    AttributeInstance* attribute_instance = attributes->get_instance(_target_attribute_tag);

    if (!attribute_instance) return;

    Variant data = p_context->get_data();

    if (data.get_type() != Variant::NIL) {
        Ref<ReactiveState> state = data;

        if (state.is_valid()) state->disconnect();
    }

    uint64_t key = EffectUtil::make_combined_key(
        static_cast<uint32_t>(p_context->get_effect_id()),
        static_cast<uint32_t>(p_context->get_modifier_index())
    );

    attribute_instance->pop_modifier(key);
}

float AttributeMod::compute(const Ref<EffectContext>& p_context) {
    float result = 0.0f;

    GDVIRTUAL_CALL(_compute, p_context, result);

    return result;
}

void AttributeMod::_reevaluate(Ref<EffectContext> p_context, int p_modifier_index) {
    AttributeSystem* attributes = EffectUtil::get_target_attributes(p_context.ptr());

    if (!attributes) return;

    AttributeInstance* attribute_instance = attributes->get_instance(_target_attribute_tag);

    if (!attribute_instance) return;

    uint64_t key = EffectUtil::make_combined_key(
        static_cast<uint32_t>(p_context->get_effect_id()),
        static_cast<uint32_t>(p_modifier_index)
    );

    float new_value = compute(p_context);

    attribute_instance->pop_modifier(key);
    attribute_instance->push_modifier(key, _operation, new_value);

}