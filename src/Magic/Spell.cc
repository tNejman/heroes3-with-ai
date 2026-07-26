#include "Magic/Spell.h"

// sf::Texture& Spell::accept( Visitor& v ) const {
//   return v.visit( *this );
// }

std::string Spell::getName() const {
  std::string name;
  switch ( this->type_ ) {
    case SpellType::MAGIC_ARROW:
      return "Magic Arrow";
    case SpellType::LIGHTNING_BOL:
      return "Lightning Bolt";
    case SpellType::DESTROY_UNDEAD:
      return "Destroy Undead";
    default:
      return "";
  }
}

SpellType Spell::getType() const {
  return this->type_;
}

uint32_t Spell::getLevel() const {
  return this->level_;
}

std::unique_ptr<Spell> Spell::copy() const {
  return std::make_unique<Spell>( this->type_ );
}
