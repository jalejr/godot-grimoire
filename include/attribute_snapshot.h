#pragma once

#include "snapshot_data.h"
#include "godot_cpp/classes/wrapped.hpp"
#include "identity_hash.h"

using namespace godot;

class AttributeSnapshot : public SnapshotData {
    GDCLASS(AttributeSnapshot, SnapshotData)

public:
    std::unordered_map<uint32_t, float, IdentityHash> values;

protected:
    static void _bind_methods();

public:
    AttributeSnapshot() = default;

    float get_value(const StringName& p_attribute_tag) const;

    Variant resolve(const StringName& p_subpath) const override;
};
