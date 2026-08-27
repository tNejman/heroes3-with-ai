#pragma once
// autor: Tomasz Nejman i Tomasz Naszkowski
/* zawarość klasa spell:
    - klasa ma pozwalać na rzucanie zaklęć
*/
#include <cstdint>
#include <memory>
#include <string>

#include "Miscellaneous/Equippable.h"

// #include "Graphics/Printable.h"

enum class MagicSchool : char { EARTH = 0, AIR = 1, FIRE = 2, WATER = 3 };

enum class SpellType : char { MAGIC_ARROW = 0, LIGHTNING_BOL = 1, DESTROY_UNDEAD = 2 };

// , public Printable
class Spell : public Equippable {
 private:
  // TODO zrobic fabryke jak art i unit
  SpellType type_;
  MagicSchool magic_school_;
  uint32_t level_{ 1 };
  uint32_t mana_cost_;

  [[nodiscard]] static MagicSchool getMagicSchoolFromSpellType( SpellType type ) noexcept;
  [[nodiscard]] static uint32_t getManaCostFromSpellType( SpellType type ) noexcept;

 public:
  // TODO rewrite to a factory
  Spell( const SpellType spell_type )
      : type_( spell_type ),
        magic_school_( getMagicSchoolFromSpellType( spell_type ) ),
        mana_cost_( getManaCostFromSpellType( spell_type ) ) {
  }
  [[nodiscard]] std::string getName() const;
  [[nodiscard]] SpellType getType() const;
  [[nodiscard]] MagicSchool getSchool() const;
  [[nodiscard]] uint32_t getLevel() const;
  [[nodiscard]] uint32_t getManaCost() const;
  [[nodiscard]] std::unique_ptr<Spell> copy() const;
};