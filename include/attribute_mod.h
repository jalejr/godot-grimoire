#pragma once

#include "effect_modifier.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/gdvirtual.gen.inc"
#include "godot_cpp/variant/string_name.hpp"
#include "attribute_types.h"

using namespace godot;

class EffectContext;

class AttributeMod : public EffectModifier {
    GDCLASS(AttributeMod, EffectModifier)

    StringName _target_attribute_tag;
    Attribute::Operation _operation = Attribute::ADD;

protected:
    static void _bind_methods();

public:
    AttributeMod() = default;
    
    StringName get_target_attribute_tag() const { return _target_attribute_tag; }
    void set_target_attribute_tag(const StringName& p_tag) { _target_attribute_tag = p_tag; }

    Attribute::Operation get_operation() const { return _operation; }
    void set_operation(Attribute::Operation p_operation) { _operation = p_operation; }

    void apply(const Ref<EffectContext>& p_context) override;
    void remove(const Ref<EffectContext>& p_context) override;

    virtual float compute(const Ref<EffectContext>& p_context);
    GDVIRTUAL1R(float, _compute, Ref<EffectContext>)

private:
    void _reevaluate(Ref<EffectContext> p_context, int p_modifier_index);
};