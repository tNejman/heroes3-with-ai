#pragma once
// autor: Tomasz Nejman i Tomasz Naszkowski
/* zawarość klasa spell:
    - klasa ma pozwalać na rzucanie zaklęć
*/
#include <cstdint>
#include <string>

enum class MagicSchool : char { EARTH, AIR, FIRE, WATER };

enum class SpellType : char { MAGIC_ARROW, LIGHTNING_BOL, DESTROY_UNDEAD };

class Spell {
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
};

