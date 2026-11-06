#include "core/Battle/SpellHandler.h"

#include <algorithm>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

#include "aux/Err.hpp"
#include "aux/Overload.hpp"
#include "core/Battle/Battle.h"
#include "core/Character/Character.h"
#include "core/Character/SecondarySkill.h"
#include "core/Game/UserCommand.h"
#include "core/Magic/SpellLib.h"
#include "engine/model/IGraphics/Visitor.h"

/* ==== @PRIVATE ==== */

[[nodiscard]] bool SpellHandler::doesSpellMagicSchoolMatchSecondarySkill(
    spell::MagicSchool spell_magic_school, SecondarySkill::Type secondary_skill_type ) noexcept {
  switch ( spell_magic_school ) {
    case spell::MagicSchool::EARTH: return secondary_skill_type == SecondarySkill::Type::EARTH_MAGIC;
    case spell::MagicSchool::AIR: return secondary_skill_type == SecondarySkill::Type::AIR_MAGIC;
    case spell::MagicSchool::FIRE: return secondary_skill_type == SecondarySkill::Type::FIRE_MAGIC;
    case spell::MagicSchool::WATER: return secondary_skill_type == SecondarySkill::Type::WATER_MAGIC;
    case spell::MagicSchool::ALL:
      return secondary_skill_type == SecondarySkill::Type::EARTH_MAGIC
             || secondary_skill_type == SecondarySkill::Type::AIR_MAGIC
             || secondary_skill_type == SecondarySkill::Type::FIRE_MAGIC
             || secondary_skill_type == SecondarySkill::Type::WATER_MAGIC;
  }

  std::unreachable();
}

[[nodiscard]] bool SpellHandler::doesCharacterHaveMatchingSpellMastery( const Character& character,
                                                                        const Spell& spell ) noexcept {
  const auto secondary_skills = character.getSecondarySkills();
  return std::ranges::find_if( secondary_skills,
                               [&]( const std::optional<SecondarySkill> maybe_skill ) {
                                 return maybe_skill.has_value()
                                        && doesSpellMagicSchoolMatchSecondarySkill( spell.getData().magic_school_,
                                                                                    maybe_skill->type_ );
                               } )
         != secondary_skills.end();
}

[[nodiscard]] std::optional<SecondarySkill> SpellHandler::getBestMatchingSecondarySkillToSpellMagicSchool(
    const Character& character, const Spell& spell ) noexcept {
  std::vector<SecondarySkill> matching_skills;

  for ( const auto maybe_secondary_skill : character.getSecondarySkills() ) {
    if ( maybe_secondary_skill.has_value()
         && doesSpellMagicSchoolMatchSecondarySkill( spell.getData().magic_school_, maybe_secondary_skill->type_ ) ) {
      matching_skills.push_back( *maybe_secondary_skill );
    }
  }
  std::optional<SecondarySkill> best_match;

  for ( const auto candidate_for_best : matching_skills ) {
    if ( !best_match.has_value() || candidate_for_best.level_ > best_match->level_ ) {
      best_match = candidate_for_best;
    }
  }

  return best_match;
}

[[nodiscard]] int SpellHandler::calculateSpellDamage( const Character& caster,
                                                      const Spell& spell_to_be_cast ) noexcept {
  /**
   * @damage calculation
   *  output_damage = base(basic/adv/expert) + Power * mult
   */
  const auto spell_damage_info = std::get<spell::effect::Damage>( spell_to_be_cast.getData().effect_ );

  const std::optional<SecondarySkill> maybe_matching_secondary_skill =
      getBestMatchingSecondarySkillToSpellMagicSchool( caster, spell_to_be_cast );
  const int power = caster.stats().getPrimarySkills().power_;

  const int base_damage = [&] {
    if ( !maybe_matching_secondary_skill.has_value() ) {
      return spell_damage_info.base_damage_[spell::effect::SECONDARY_SKILL_BASIC_BASE_DAMAGE_IDX];
    }
    switch ( maybe_matching_secondary_skill->level_ ) {
      case SecondarySkill::Level::BASIC:
        return spell_damage_info.base_damage_[spell::effect::SECONDARY_SKILL_BASIC_BASE_DAMAGE_IDX];
      case SecondarySkill::Level::ADVANCED:
        return spell_damage_info.base_damage_[spell::effect::SECONDARY_SKILL_ADVANCED_BASE_DAMAGE_IDX];
      case SecondarySkill::Level::EXPERT:
        return spell_damage_info.base_damage_[spell::effect::SECONDARY_SKILL_EXPERT_BASE_DAMAGE_IDX];
    }

    std::unreachable();
  }();

  const int calculated_damage = base_damage + ( power * spell_damage_info.mult_ );

  return calculated_damage;
}

void SpellHandler::handleDamageSpell( const BattleCommand& command, Battle& battle ) noexcept {
  const auto& caster = *battle.getCurrentCharacter();  // non null; checked in handleSpell
  const Spell spell_to_be_cast = *command.maybe_spell_;

  const int spell_damage = calculateSpellDamage( caster, spell_to_be_cast );

  auto& unit = *battle.getUnitFromCoords( command.destination_ );  // can't be null, all generated commands are safe
  unit.modifyCurrentHealth( spell_damage );

  if ( !unit.isAlive() ) {
    battle.killUnit( unit );
  }
}

void SpellHandler::handleBuffSpell( const BattleCommand& /*command*/, Battle& /*battle*/ ) noexcept {
  err::abort( "not implemented" );
}

void SpellHandler::handleSummonSpell( const BattleCommand& /*command*/, Battle& /*battle*/ ) noexcept {
  err::abort( "not implemented" );
}

void SpellHandler::handleSpecialSpell( const BattleCommand& /*command*/, Battle& /*battle*/ ) noexcept {
  err::abort( "not implemented" );
}

/* ==== @PUBLIC ==== */

void SpellHandler::handleSpell( const BattleCommand& command, Battle& battle ) noexcept {
  auto* caster = battle.getCurrentCharacter();
  err::passCondOrAbort( caster != nullptr, "current_character_ in battle is null" );
  const bool is_mana_discount_allowed = doesCharacterHaveMatchingSpellMastery( *caster, *command.maybe_spell_ );

  const int mana_cost = ( is_mana_discount_allowed ) ? command.maybe_spell_->getData().mana_cost_mastery_
                                                     : command.maybe_spell_->getData().mana_cost_default_;
  caster->stats().spendMana( mana_cost );

  // "visit" instead of "if constexpr", because it's exhaustive
  std::visit( Overload{
                  [&]( const spell::effect::Damage ) { handleDamageSpell( command, battle ); },
                  [&]( const spell::effect::UnitBuff ) { handleBuffSpell( command, battle ); },
                  [&]( const spell::effect::Summon ) { handleSummonSpell( command, battle ); },
                  [&]( const spell::effect::Special ) { handleSpecialSpell( command, battle ); },
              },
              ( *command.maybe_spell_ ).getData().effect_ );
}