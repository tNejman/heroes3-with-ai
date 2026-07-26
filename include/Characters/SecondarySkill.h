#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/
// #include <SFML/Graphics.hpp>

#include <stdint.h>

#include <memory>
#include <string>

#include "Exceptions/BadCopyException.hpp"
#include "Miscellaneous/Printable.h"
#include "Miscellaneous/ProjectLib.h"

enum class SecondarySkillType : int {
  AIR_MAGIC = 0,
  FIRE_MAGIC = 1,
  EARTH_MAGIC = 2,
  WATER_MAGIC = 3
};

enum class SecondarySkillLevel : int {
  BASIC = 0,
  ADVANCED = 1,
  EXPERT = 2
};

class SecondarySkill : public Printable {
  // TODO zrobic fabryke
  const SecondarySkillType type_;
  SecondarySkillLevel level_;
  uint32_t cost_;

 public:
  SecondarySkill( SecondarySkillType skill_type );
  sf::Texture& accept( Visitor& v ) const;
  SecondarySkillType getType() const;
  SecondarySkillLevel getLevel() const;
  std::string getName() const;
  std::unique_ptr<SecondarySkill> copy() const;
};

// class AirMagic : public SecondarySkill {};
// class EarthMagic : public SecondarySkill {};
// class FireMagic : public SecondarySkill {};
// class WaterMagic : public SecondarySkill {};
// class Wisdom : public SecondarySkill {};
