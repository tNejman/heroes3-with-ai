#include "core/Magic/Spell.h"

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

SpellType Spell::getType() const {
  return this->type_;
}

uint32_t Spell::getLevel() const {
  return this->level_;
}