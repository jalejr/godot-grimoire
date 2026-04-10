# Grimoire
A GAS-inspired gameplay systems plugin for Godot 4, built with GDExtension in C++.
 
Grimoire brings the core ideas behind Unreal Engine's Gameplay Ability System to Godot — structured ability activation, tag-driven state management, attribute modifiers, and event-based effect application
 
> ⚠️ **VERY WIP** — Grimoire is actively developed and APIs may change between releases. It is usable but not yet production hardened. Feedback and bug reports are welcome.

---
 
## Installation
 
1. Download the latest release zip
2. Extract into your Godot project — you should get:
```
addons/
    tag_system/
    grimoire/
```
3. Enable tag plugin in **Project Settings → Plugins**
4. Reload the project
5. If you see a Tags tab at the top then you're good to go
 
---
 
## Quick Example
 
Define a tag and give an entity a TagContainer:
 
```gdscript
# Tags are accessed through the generated Tag constants
var container: TagContainer = $TagContainer
container.add_tag(Tag.STATUS_BUFF_STRENGTH)
 
# Hierarchical queries — has any Status tag?
print(container.has_tag(Tag.STATUS))           # true
print(container.has_tag(Tag.STATUS, true))     # false (exact match)
 
# Watch for tag changes
container.watch_tag(Tag.STATUS, _on_status_changed)
 
func _on_status_changed(tag: StringName, count: int) -> void:
    print("%s count is now %d" % [tag, count])
```
	
Activate an ability:
 
```gdscript
var ability_system: AbilitySystem = $AbilitySystem
ability_system.try_activate(Tag.ABILITY_ATTACK_MELEE)
```
 
Apply an effect:
 
```gdscript
var effect_system: EffectSystem = $EffectSystem
effect_system.apply_effect(poison_effect_definition, source_entity)
```
 
---
	
## Architecture
 
Grimoire follows the same structural ideas as GAS but is designed for GDScript-first workflows. The heavy lifting is in C++ for performance and the user-facing API is in GDScript virtual methods.
 
Each system is a `Node` you attach to your entity. A typical entity scene looks like:
 
```
CharacterBody2D / Node3D / etc.
├── TagContainer
├── AttributeSystem
├── EventSystem
├── EffectSystem
└── AbilitySystem
```

At its core Grimoire is five systems that work together:
 
- **TagSystem** — A hierarchical tag registry. Tags like `Ability.Attack.Melee` and `Status.Debuff.Poison` are registered once and used everywhere. Any node can carry a `TagContainer` and watch for tag changes reactively.
- **AttributeSystem** — Define stats like health, stamina, and speed as `AttributeDefinition` resources. Modifiers stack cleanly with flat add, multiply, and override operations. Constraints enforce min/max boundaries.
- **EventSystem** — An entity-scoped signal bus keyed by tags. Emit `Event.Combat.Hit` and any watcher of `Event.Combat` or `Event` is also notified. No hardcoded signal names.
- **EffectSystem** — Apply instant, duration, and periodic effects to entities through a shared EffectContext. Effects execute any number of EffectModifier resources — what those modifiers do is entirely up to you. Attribute changes, tag grants, event emissions, or custom game logic are all valid implementations.
- **AbilitySystem** — Define abilities as resources with activation requirements, costs, and state machines. Abilities activate from input or trigger automatically when tags appear. GDScript handles the logic via virtual methods.
 
---

Systems communicate through the tag layer rather than direct references. Effects grant tags, abilities watch for tags, the event system fires tag-keyed signals. This keeps systems decoupled and makes behavior composable.

## Repo Structure
 
Grimoire uses a split source/build architecture:
 
| Repo | Purpose |
|------|---------|
| [tag-system-src](https://github.com/jalejr/tag-system-src) | TagSystem source |
| [attribute-system-src](https://github.com/jalejr/attribute-system-src) | AttributeSystem source |
| [event-system-src](https://github.com/jalejr/event-system-src) | EventSystem source |
| [effect-system-src](https://github.com/jalejr/effect-system-src) | EffectSystem source |
| [ability-system-src](https://github.com/jalejr/ability-system-src) | AbilitySystem source |
| **This repo** | Full stack build — compiles all systems into one GDExtension |
 
Individual systems currently not available with only the tag system being an exception at the moment.

Every system is dependent on the tag system and some refactoring is necessary at the moment to make systems truly separate

---
 
## License
 
MIT
