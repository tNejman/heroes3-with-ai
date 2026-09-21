#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/

#include <memory>

#include "engine/Graphics/Visitor.h"

class SecondarySkill {
 public:
  enum class Type : char { AIR_MAGIC, FIRE_MAGIC, EARTH_MAGIC, WATER_MAGIC };

  enum class Level : char { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

 private:
  // TODO zrobic fabryke
  SecondarySkill::Type type_;
  SecondarySkill::Level level_;

  constexpr SecondarySkill( SecondarySkill::Type skill_type ) noexcept;
  constexpr SecondarySkill( SecondarySkill::Type skill_type, SecondarySkill::Level skill_level ) noexcept;

 public:
  static std::unique_ptr<SecondarySkill> create( SecondarySkill::Type type, SecondarySkill::Level level );
  static std::unique_ptr<SecondarySkill> create( SecondarySkill::Type type );

  [[nodiscard]] SecondarySkill::Type getType() const;
  [[nodiscard]] SecondarySkill::Level getLevel() const;
  [[nodiscard]] SecondarySkill copy() const;
};
