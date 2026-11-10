#include "core/Magic/SpellBook.h"

#include <vector>

#include "core/Magic/Spell.h"

[[nodiscard]] const std::vector<Spell>& SpellBook::getSpells() const noexcept {
  return spells_;
}

void SpellBook::learnSpell( Spell spell ) {
  spells_.push_back( spell );
}

SpellBook SpellBook::copy() const {
  SpellBook copy{};
  copy.spells_ = this->spells_;
  return copy;
}
