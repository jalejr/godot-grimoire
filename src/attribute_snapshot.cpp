#include "attribute_snapshot.h"
#include "tag_manager.h"

using namespace godot;

void AttributeSnapshot::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_value", "attribute_tag"),
        &AttributeSnapshot::get_value);
}

float AttributeSnapshot::get_value(const StringName& p_attribute_tag) const {
    TagManager* tag_manager = TagManager::get_singleton();

    if (!tag_manager) return 0.0f;

    uint32_t index = tag_manager->get_tag_index(p_attribute_tag);

    if (index == TagManager::INVALID_INDEX) return 0.0f;

    auto it = values.find(index);

    return it != values.end() ? it->second : 0.0f;
}

Variant AttributeSnapshot::resolve(const StringName& p_subpath) const {
    if (String(p_subpath).is_empty()) return Variant();
    return get_value(p_subpath);
}

