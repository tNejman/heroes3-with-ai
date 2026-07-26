#include "Magic/SpellBook.h"

SpellBook::SpellBook() {};
SpellBook::~SpellBook() {};

void SpellBook::learnSpell( std::unique_ptr<Spell> spell ) {
  spells_.push_back( std::move( spell ) );
  return;
}

std::unique_ptr<SpellBook> SpellBook::copy() const {
  std::unique_ptr<SpellBook> copy = std::make_unique<SpellBook>();
  for ( const auto& spell : spells_ ) {
    copy->spells_.push_back( spell->copy() );
  }
  return copy;
}
