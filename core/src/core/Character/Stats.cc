#include "core/Character/Stats.h"

[[nodiscard]] const character::Stats::PrimarySkills& character::Stats::getPrimarySkills() const noexcept {
  return primary_skills_;
}

[[nodiscard]] const character::Stats::Level& character::Stats::getLevel() const noexcept {
  return level_;
}

[[nodiscard]] const character::Stats::Mana& character::Stats::getMana() const noexcept {
  return mana_;
}

void character::Stats::spendMana( int amount ) noexcept {
  mana_.current_mana_ -= amount;
}

[[nodiscard]] const character::Stats::Misc& character::Stats::getMisc() const noexcept {
  return misc_;
}

[[nodiscard]] const character::Stats::Movement& character::Stats::getMovement() const noexcept {
  return movement_;
}