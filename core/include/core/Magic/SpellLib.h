#pragma once

#include <algorithm>
#include <array>
#include <magic_enum/magic_enum.hpp>
#include <variant>

#include "aux/DisableCopyMoveStructHelper.hpp"
#include "core/Character/SecondarySkill.h"
#include "core/Unit/UnitsLib.h"

/** Variety of effects
# stat
        speed
        defense
        luck
        attack

# kinda stat
        ranged attack
        air spell defense
        reduced damage from hand to hand attacks
        reduced damage from earth spells
        reduce morale

# effect?
        take control over unit
        retaliate against additional attacks
        chance to reflect spell
        summon
        reanimate undead creatures
        damage to castle walls
        make obstacle

*/

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
  enum class Side : char { ALLY, ENEMY, ANY };
  const Side side_;

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

struct UnitBuff {  // also debuff, just put negative
  // @TODO what is buffed?
  enum class Type : char { ATTACK, DEFENSE, SPEED, LUCK, MORALE };
  Type type_;

  using Flat = std::array<int, SECONDARY_SKILL_LEVEL_OPTIONS>;
  using Mult = std::array<double, SECONDARY_SKILL_LEVEL_OPTIONS>;
  const std::variant<Flat, Mult> intensity_;

  // duration ~=~ hero spell power
};

struct Summon {
  const UnitData& unit_data_;
};

struct Special {
  // what does it do?
};

};  // namespace effect
using Effect = std::variant<effect::Damage, effect::UnitBuff, effect::Summon, effect::Special>;

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

static_assert( magic_enum::enum_count<SecondarySkill::Level>() == effect::SECONDARY_SKILL_LEVEL_OPTIONS,
               "Required for damage calculation" );

constexpr inline std::array BASE_PRESET = {
    //** COMBAT DAMAGE SPELLS */
    spell::BaseData{ .type_ = Type::MAGIC_ARROW,
                     .magic_school_ = MagicSchool::ALL,
                     .level_ = 1,
                     .mana_cost_default_ = 5,
                     .mana_cost_mastery_ = 4,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_ = spell::effect::Damage{ .base_damage_ = { 10, 20, 30 }, .mult_ = 10 } },

    spell::BaseData{ .type_ = Type::LIGHTNING_BOLT,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 2,
                     .mana_cost_default_ = 10,
                     .mana_cost_mastery_ = 8,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_ = spell::effect::Damage{ .base_damage_ = { 10, 20, 50 }, .mult_ = 25 } },

    spell::BaseData{ .type_ = Type::DESTROY_UNDEAD,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 3,
                     .mana_cost_default_ = 15,
                     .mana_cost_mastery_ = 12,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::All{} },
                     .effect_ = spell::effect::Damage{ .base_damage_ = { 10, 20, 50 }, .mult_ = 10 } },

    //** COMBAT UTILITY SPELLS */
    //**    BUFF */
    spell::BaseData{
        .type_ = Type::HASTE,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 1,
        .mana_cost_default_ = 6,
        .mana_cost_mastery_ = 5,
        .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Count{ .min_targets_ = 1, .max_targets_ = 7 } },
        .effect_ = spell::effect::UnitBuff{ .type_ = spell::effect::UnitBuff::Type::SPEED,
                                            .intensity_ = spell::effect::UnitBuff::Flat{ 3, 3, 5 } } },

    spell::BaseData{
        .type_ = Type::FORTUNE,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 2,
        .mana_cost_default_ = 7,
        .mana_cost_mastery_ = 5,
        .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Count{ .min_targets_ = 1, .max_targets_ = 7 } },
        .effect_ = spell::effect::UnitBuff{ .type_ = spell::effect::UnitBuff::Type::LUCK,
                                            .intensity_ = spell::effect::UnitBuff::Flat{ 1, 1, 2 } } },

    //**    DEBUFF */
    spell::BaseData{ .type_ = Type::DISRUPTING_RAY,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 2,
                     .mana_cost_default_ = 10,
                     .mana_cost_mastery_ = 8,
                     .target_{ .side_ = Target::Side::ENEMY, .target_ = Target::Single{} },
                     .effect_ = spell::effect::UnitBuff{ .type_ = spell::effect::UnitBuff::Type::DEFENSE,
                                                         .intensity_ = spell::effect::UnitBuff::Flat{ -3, -4, -5 } } },

    spell::BaseData{ .type_ = Type::HYPNOTIZE,
                     .magic_school_ = MagicSchool::AIR,
                     .level_ = 3,
                     .mana_cost_default_ = 18,
                     .mana_cost_mastery_ = 15,
                     .target_{ .side_ = Target::Side::ALLY, .target_ = Target::Single{} },
                     .effect_ = spell::effect::Special{ /* take control over enemy unit*/ } },

    //**    UTILITY */
    spell::BaseData{
        .type_ = Type::SUMMON_AIR_ELEMENTAL,
        .magic_school_ = MagicSchool::AIR,
        .level_ = 5,
        .mana_cost_default_ = 25,
        .mana_cost_mastery_ = 20,
        .target_{
            .side_ = Target::Side::ALLY,
            .target_ = Target::AOE{ .diameter_ = 1, .forced_location_ = Target::AOE::Location::EMPTY_TILE },
        },
        .effect_ = spell::effect::Summon{ getUnitDataFromType( ConfluxUnitType::AIR_ELEMENTAL ) } },
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

consteval bool doSpellTypesMatchArrayLocations() {
  for ( size_t i = 0; i < spell::BASE_PRESET.size(); ++i ) {
    const auto& spell_data = BASE_PRESET[i];
    if ( spell_data.type_ != static_cast<spell::Type>( i ) ) {
      return false;
    }
  }
  return true;
}

static_assert( doSpellTypesMatchArrayLocations() );

}  // namespace spell