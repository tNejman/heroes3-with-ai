#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/
// #include <SFML/Graphics.hpp>

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <memory>
#include <string>

#include "Graphics/Printable.h"

enum class SecondarySkillType : int { AIR_MAGIC = 0, FIRE_MAGIC = 1, EARTH_MAGIC = 2, WATER_MAGIC = 3 };

enum class SecondarySkillLevel : int { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

class SecondarySkill : public Printable {
  // TODO zrobic fabryke
  SecondarySkillType type_;
  SecondarySkillLevel level_;
  uint32_t cost_;

 public:
  SecondarySkill( SecondarySkillType skill_type );
  sf::Texture& accept( Visitor& vis ) const;
  [[nodiscard]] SecondarySkillType getType() const;
  [[nodiscard]] SecondarySkillLevel getLevel() const;
  [[nodiscard]] std::string getName() const;
  [[nodiscard]] std::unique_ptr<SecondarySkill> copy() const;
};

// class AirMagic : public SecondarySkill {};
// class EarthMagic : public SecondarySkill {};
// class FireMagic : public SecondarySkill {};
// class WaterMagic : public SecondarySkill {};
// class Wisdom : public SecondarySkill {};
