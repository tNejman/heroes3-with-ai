#include "Magic/SpellBook.h"

#include <memory>
#include <utility>

#include "Magic/Spell.h"

void SpellBook::learnSpell( std::unique_ptr<Spell> spell ) {
  spells_.push_back( std::move( spell ) );
}

std::unique_ptr<SpellBook> SpellBook::copy() const {
  std::unique_ptr<SpellBook> copy = std::make_unique<SpellBook>();
  for ( const auto& spell : spells_ ) {
    copy->spells_.push_back( spell->copy() );
  }
  return copy;
}
