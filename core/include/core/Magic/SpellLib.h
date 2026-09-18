#pragma once

#include <algorithm>
#include <array>
#include <variant>

#include "aux/DisableCopyMoveStructHelper.hpp"
#include "core/Character/Character.h"
#include "core/Character/SecondarySkill.h"
#include "core/Unit/UnitsLib.h"
#include "magic_enum/magic_enum.hpp"

namespace spell {

enum class Type : char {
  // Combat Damage Spells
  MAGIC_ARROW,
  LIGHTNING_BOLT,
  DESTROY_UNDEAD,

  // Combat Utility Spells
  //    Buff
  HASTE,
  FORTUNE,
  PRECISION,
  //    Debuff
  DISRUPTING_RAY,
  HYPNOTIZE,
  //    Utility
  SUMMON_AIR_ELEMENTAL,
  QUICKSAND,

  // Adventure Map Spells
  // @TODO for now not implemented (spells relate to visio)
};

enum class MagicSchool : char { EARTH, AIR, FIRE, WATER, ALL };

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
struct Target {
  enum class Side : char { ALLY, ENEMY, ALL } side_;

  struct Single {};
  struct All {};

  struct Count {
    const int min_targets_;
    const int max_targets_;
  };
  struct AOE {
    const int diameter_;
    enum class Location : char { UNIT, EMPTY_TILE, NO_FORCE } forced_location_;
  };

  const std::variant<Single, All, Count, AOE> target_;
};

namespace effect {

constexpr inline int SECONDARY_SKILL_LEVEL_OPTIONS = 3;

struct Damage {
  const std::array<int, SECONDARY_SKILL_LEVEL_OPTIONS> base_damage_;
  const int mult_;
};

struct Buff {  // also debuff, just put negative
  // @TODO what is buffed?
  using Flat = int;
  using Mult = float;
  const std::variant<Flat, Mult> intensity_;
};

struct Summon {
  const UnitData& unit_data_;
};

};  // namespace effect
using Effect = std::variant<effect::Damage, effect::Buff, effect::Summon>;

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct BaseData {
  const spell::Type type_;
  const spell::MagicSchool magic_school_;
  const int level_;
  const int mana_cost_default_;
  const int mana_cost_mastery_;
  const Target target_;
  const Effect effect_;

  [[no_unique_address]] DisableCopyMove _no_copy_move{};

  //   constexpr bool operator==( const spell::BaseData& other ) const noexcept = default;
};
// NOLINTEND(misc-non-private-member-variables-in-classes)
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)

static_assert( magic_enum::enum_count<secondary_skill::Level>() == 3, "Required for damage calculation" );

constexpr inline std::array BASE_PRESET = {
    //** COMBAT DAMAGE SPELLS */
    spell::BaseData{ .type_ = Type::MAGIC_ARROW,
                     .magic_school_ = MagicSchool::ALL,
                     .level_ = 1,
                     .mana_cost_default_ = 5,
                     .mana_cost_mastery_ = 4,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_ = effect::Damage{ .base_damage_ = { 10, 20, 30 }, .mult_ = 10 } },

    spell::BaseData{ .type_ = Type::LIGHTNING_BOLT,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 2,
                     .mana_cost_default_ = 10,
                     .mana_cost_mastery_ = 8,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_ = effect::Damage{ .base_damage_ = { 10, 20, 50 }, .mult_ = 25 } },

    spell::BaseData{ .type_ = Type::DESTROY_UNDEAD,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 3,
                     .mana_cost_default_ = 15,
                     .mana_cost_mastery_ = 12,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::All{} },
                     .effect_ = effect::Damage{ .base_damage_ = { 10, 20, 50 }, .mult_ = 10 } },

    //** COMBAT UTILITY SPELLS */
    //**    BUFF */
    spell::BaseData{
        .type_ = Type::HASTE,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 1,
        .mana_cost_default_ = 6,
        .mana_cost_mastery_ = 5,
        .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Count{ .min_targets_ = 1, .max_targets_ = 7 } },
        .effect_{} },

    spell::BaseData{
        .type_ = Type::FORTUNE,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 2,
        .mana_cost_default_ = 7,
        .mana_cost_mastery_ = 5,
        .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Count{ .min_targets_ = 1, .max_targets_ = 7 } },
        .effect_{} },

    spell::BaseData{
        .type_ = Type::PRECISION,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 2,
        .mana_cost_default_ = 7,
        .mana_cost_mastery_ = 5,
        .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Count{ .min_targets_ = 1, .max_targets_ = 7 } },
        .effect_{} },

    //**    DEBUFF */
    spell::BaseData{ .type_ = Type::DISRUPTING_RAY,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 2,
                     .mana_cost_default_ = 10,
                     .mana_cost_mastery_ = 8,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_{} },

    spell::BaseData{ .type_ = Type::HYPNOTIZE,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 3,
                     .mana_cost_default_ = 18,
                     .mana_cost_mastery_ = 15,
                     .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Single{} },
                     .effect_{} },

    //**    UTILITY */
    spell::BaseData{ .type_ = Type::SUMMON_AIR_ELEMENTAL,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 5,
                     .mana_cost_default_ = 25,
                     .mana_cost_mastery_ = 20,
                     .target_{ .side_ = Target::Side::ALLY, .target_ = Target::AOE{ .diameter_ = 1 } },
                     .effect_{} },

    spell::BaseData{ .type_ = Type::QUICKSAND,
                     .magic_school_ = MagicSchool::EARTH,
                     .level_ = 2,
                     .mana_cost_default_ = 8,
                     .mana_cost_mastery_ = 6,
                     .target_{ .side_ = Target::Side::ALLY, .target_ = Target::AOE{ .diameter_ = 0 } },
                     .effect_{} },
};

constexpr inline int MIN_LEVEL = 1;
constexpr inline int MAX_LEVEL = 5;

consteval bool isLevelInRange( const spell::BaseData& spell_data ) {
  return spell_data.level_ >= spell::MIN_LEVEL && spell_data.level_ <= spell::MAX_LEVEL;
}

constexpr inline int MIN_MANA_COST = 0;
constexpr inline int MAX_MANA_COST = 100;

consteval bool isManaInRange( const spell::BaseData& spell_data ) {
  return spell_data.mana_cost_default_ >= spell::MIN_MANA_COST && spell_data.mana_cost_default_ <= spell::MAX_MANA_COST
         && spell_data.mana_cost_mastery_ >= spell::MIN_MANA_COST
         && spell_data.mana_cost_mastery_ <= spell::MAX_MANA_COST;
}

consteval bool isNotAoeOrIsAoeInRange( const spell::BaseData& spell_data ) {
  return !std::holds_alternative<Target::AOE>( spell_data.target_.target_ )
         || std::get<Target::AOE>( spell_data.target_.target_ ).diameter_ >= 0;
}

static_assert( std::ranges::all_of( spell::BASE_PRESET, []( const spell::BaseData& spell_data ) {
  return isLevelInRange( spell_data ) && isManaInRange( spell_data ) && isNotAoeOrIsAoeInRange( spell_data );
} ) );

consteval bool allSpellTypesUsed() {
  std::array<bool, static_cast<size_t>( magic_enum::enum_count<spell::Type>() )> seen = {};
  for ( const auto& spell_data : spell::BASE_PRESET ) {
    seen[static_cast<size_t>( spell_data.type_ )] = true;
  }
  return std::ranges::all_of( seen, []( bool b ) { return b; } );
}

static_assert( allSpellTypesUsed() );

}  // namespace spell