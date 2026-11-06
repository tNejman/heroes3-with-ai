#pragma once

#include <optional>

#include "core/Character/SecondarySkill.h"
#include "core/Game/UserCommand.h"
#include "core/Magic/SpellLib.h"
#include "engine/model/IGraphics/Visitor.h"

class SpellHandler {
 private:
  [[nodiscard]] static bool doesSpellMagicSchoolMatchSecondarySkill( spell::MagicSchool,
                                                                     SecondarySkill::Type ) noexcept;
  [[nodiscard]] static bool doesCharacterHaveMatchingSpellMastery( const Character&, const Spell& ) noexcept;
  [[nodiscard]] static std::optional<SecondarySkill> getBestMatchingSecondarySkillToSpellMagicSchool(
      const Character&, const Spell& ) noexcept;
  [[nodiscard]] static int calculateSpellDamage( const Character&, const Spell& ) noexcept;

  static void handleDamageSpell( const BattleCommand&, Battle& ) noexcept;
  static void handleBuffSpell( const BattleCommand&, Battle& ) noexcept;
  static void handleSummonSpell( const BattleCommand&, Battle& ) noexcept;
  static void handleSpecialSpell( const BattleCommand&, Battle& ) noexcept;

 public:
  SpellHandler() = delete;

  static void handleSpell( const BattleCommand&, Battle& ) noexcept;
};