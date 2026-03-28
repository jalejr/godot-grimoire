#include "ability_util.h"

#include "ability_system.h"
#include "attribute_system.h"
#include "effect_system.h"
#include "event_system.h"
#include "tag_container.h"


using namespace godot;

void AbilityUtil::_bind_methods() {
    ClassDB::bind_static_method("AbilityUtil",
        D_METHOD("get_owner", "ability_system"), &AbilityUtil::get_owner);
    ClassDB::bind_static_method("AbilityUtil",
        D_METHOD("get_attributes", "ability_system"), &AbilityUtil::get_attributes);
    ClassDB::bind_static_method("AbilityUtil",
        D_METHOD("get_effects", "ability_system"), &AbilityUtil::get_effects);
    ClassDB::bind_static_method("AbilityUtil",
        D_METHOD("get_tags", "ability_system"), &AbilityUtil::get_tags);
    ClassDB::bind_static_method("AbilityUtil",
        D_METHOD("get_events", "ability_system"), &AbilityUtil::get_events);
}

Node* AbilityUtil::get_owner(AbilitySystem *p_system) {
    ERR_FAIL_NULL_V_MSG(p_system, nullptr,
        "AbilityUtil::get_owner: null AbilitySystem passed. "
        "Call as AbilityUtil.get_owner(ability_system) from AbilityLogic.");
 
    Node* owner = p_system->get_owner();
    ERR_FAIL_NULL_V_MSG(owner, nullptr,
        "AbilityUtil::get_owner: AbilitySystem has no owner. "
        "Ensure AbilitySystem is part of a saved scene — "
        "nodes created purely in code have no owner.");
    
    return owner;
}

AttributeSystem* AbilityUtil::get_attributes(AbilitySystem *p_system) {
    Node* owner = get_owner(p_system);
    AttributeSystem* attributes = Object::cast_to<AttributeSystem>(
        owner->get_node_or_null("AttributeSystem")
    );

    ERR_FAIL_NULL_V_MSG(attributes, nullptr,
        "AbilityUtil::get_attributes: no AttributeSystem child named "
        "'AttributeSystem' found on owner. "
        "Check node name matches exactly.");
    return attributes;
}

EffectSystem* AbilityUtil::get_effects(AbilitySystem *p_system) {
    Node* owner = get_owner(p_system);
    EffectSystem* effects = Object::cast_to<EffectSystem>(
        owner->get_node_or_null("EffectSystem")
    );

    ERR_FAIL_NULL_V_MSG(effects, nullptr,
        "AbilityUtil::get_effects: no EffectSystem child named "
        "'EffectSystem' found on owner. "
        "Check node name matches exactly.");
    return effects;
}

TagContainer* AbilityUtil::get_tags(AbilitySystem *p_system) {
    TagContainer* tags = p_system->get_tag_container();
    ERR_FAIL_NULL_V_MSG(tags, nullptr,
        "AbilityUtil::get_tags: AbilitySystem has no tag_container assigned. "
        "Drag a TagContainer into the tag_container export slot in the inspector.");

    return tags;
}

EventSystem* AbilityUtil::get_events(AbilitySystem *p_system) {
    Node* owner = get_owner(p_system);

    EventSystem* events = Object::cast_to<EventSystem>(
        owner->get_node_or_null("EffectSystem")
    );

    ERR_FAIL_NULL_V_MSG(events, nullptr,
        "AbilityUtil::get_events: no EventSystem child named "
        "'EventSystem' found on owner. "
        "Check node name matches exactly.");
    return events;
}