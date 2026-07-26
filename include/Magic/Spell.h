#pragma once
// autor: Tomasz Nejman i Tomasz Naszkowski
/* zawarość klasa spell:
    - klasa ma pozwalać na rzucanie zaklęć
*/
#include <stdint.h>

#include <memory>
#include <string>

#include "Miscellaneous/Equippable.h"
// #include "Miscellaneous/Printable.h"

enum class MagicSchool : int { EARTH = 0, AIR = 1, FIRE = 2, WATER = 3 };

enum class SpellType : int { MAGIC_ARROW = 0, LIGHTNING_BOL = 1, DESTROY_UNDEAD = 2 };

// , public Printable
class Spell : public Equippable {
 private:
  // TODO zrobic fabryke jak art i unit
  const SpellType type_;
  MagicSchool magic_school_;
  uint32_t level_;
  uint32_t mana_cost_;

 public:
  Spell( const SpellType spell_type )
      : type_( spell_type ) {
          // magic_shcool_ = TODO automatyczne przypisanie
        };
  // sf::Texture& accept( Visitor& v ) const override;
  std::string getName() const;
  SpellType getType() const;
  MagicSchool getSchool() const;
  uint32_t getLevel() const;
  uint32_t getManaCost() const;
  std::unique_ptr<Spell> copy() const;
};