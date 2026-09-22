#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/

struct SecondarySkill {
  enum class Type : char { AIR_MAGIC, FIRE_MAGIC, EARTH_MAGIC, WATER_MAGIC };
  enum class Level : char { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

  SecondarySkill::Type type_;
  SecondarySkill::Level level_;
};