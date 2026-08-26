#include "Magic/Spell.h"

#include <cstdint>
#include <memory>
#include <string>

MagicSchool Spell::getMagicSchoolFromSpellType( SpellType type ) noexcept {
  switch ( type ) {
    case SpellType::MAGIC_ARROW:
    case SpellType::LIGHTNING_BOL:
    case SpellType::DESTROY_UNDEAD: return MagicSchool::AIR;  // TODO implement actual types
  }
}

uint32_t Spell::getManaCostFromSpellType( SpellType type ) noexcept {
  switch ( type ) {
    case SpellType::MAGIC_ARROW:
    case SpellType::LIGHTNING_BOL:
    case SpellType::DESTROY_UNDEAD: return 0U;  // TODO implement actual cost
  }
}

std::string Spell::getName() const {
  // TODO don't return by value
  switch ( this->type_ ) {
    case SpellType::MAGIC_ARROW: return "Magic Arrow";
    case SpellType::LIGHTNING_BOL: return "Lightning Bolt";
    case SpellType::DESTROY_UNDEAD: return "Destroy Undead";
    default: return "";
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
