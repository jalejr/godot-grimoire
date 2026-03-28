#include "effect_util.h"

#include "effect_system.h"
#include "tag_container.h"

using namespace godot;

void EffectUtil::_bind_methods() {
    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_source_attributes", "context"), &EffectUtil::get_source_attributes);
    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_target_attributes", "context"), &EffectUtil::get_target_attributes);

    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_source_tag_container", "context"),  &EffectUtil::get_source_tag_container);
    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_target_tag_container", "context"),  &EffectUtil::get_target_tag_container);

    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_source_events", "context"), &EffectUtil::get_source_events);
    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_target_events", "context"), &EffectUtil::get_target_events);
 
    ClassDB::bind_static_method("EffectUtil",
        D_METHOD("get_snapshot_attributes", "context"), &EffectUtil::get_snapshot_for_attributes);
}

AttributeSystem* EffectUtil::get_source_attributes(EffectContext* p_context) {
    if (!p_context || !p_context->get_source_system()) return nullptr;
    return _find_attributes(p_context->get_source_system()->get_parent());
}
AttributeSystem* EffectUtil::get_target_attributes(EffectContext* p_context) {
    if (!p_context || !p_context->get_target_system()) return nullptr;
    return _find_attributes(p_context->get_target_system()->get_parent());
}

TagContainer* EffectUtil::get_source_tag_container(EffectContext* p_context) {
    if (!p_context || !p_context->get_source_system()) return nullptr;
    return _find_tag_container(p_context->get_source_system()->get_parent());
}
TagContainer* EffectUtil::get_target_tag_container(EffectContext* p_context) {
    if (!p_context || !p_context->get_target_system()) return nullptr;
    return _find_tag_container(p_context->get_target_system()->get_parent());
}

EventSystem* EffectUtil::get_source_events(EffectContext* p_context) {
    if (!p_context || !p_context->get_source_system()) return nullptr;
    return _find_events(p_context->get_target_system()->get_parent());
}
EventSystem* EffectUtil::get_target_events(EffectContext* p_context) {
    if (!p_context || !p_context->get_target_system()) return nullptr;
    return _find_events(p_context->get_target_system()->get_parent());
}

Ref<AttributeSnapshot> EffectUtil::get_snapshot_for_attributes(EffectContext* p_context) {
    if (!p_context) return nullptr;
    return p_context->get_snapshot_object<AttributeSnapshot>(StringName("attributes"));
}

AttributeSystem* EffectUtil::_find_attributes(Node* p_effect_system_owner) {
    if (!p_effect_system_owner) return nullptr;
    return Object::cast_to<AttributeSystem>(
        p_effect_system_owner->get_node_or_null("AttributeSystem")
    );
}

TagContainer* EffectUtil::_find_tag_container(Node* p_effect_system_owner) {
    if (!p_effect_system_owner) return nullptr;
    return Object::cast_to<TagContainer>(
        p_effect_system_owner->get_node_or_null("TagContainer")
    );
}

EventSystem* EffectUtil::_find_events(Node* p_effect_system_owner) {
    if (!p_effect_system_owner) return nullptr;
    return Object::cast_to<EventSystem>(
        p_effect_system_owner->get_node_or_null("EventSystem")
    );
}