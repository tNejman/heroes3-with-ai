#include "core/Magic/SpellBook.h"

#include "core/Magic/Spell.h"

void SpellBook::learnSpell( Spell spell ) {
  spells_.push_back( spell );
}

SpellBook SpellBook::copy() const {
  SpellBook copy{};
  copy.spells_ = this->spells_;
  return copy;
}
