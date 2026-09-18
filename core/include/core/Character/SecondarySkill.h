#pragma once
// Autor: Tomasz Nejman
/* Zawartość klasy SecondarySkill:
  - Klasa SecondarySkill odpowiada za umiejętności drugorzędne postaci.
  - Zawiera metody do zarządzania poziomem umiejętności, kosztami i typem umiejętności.
*/

#include <cstdint>
#include <memory>

#include "engine/Graphics/IPrintable.h"
#include "engine/Graphics/Visitor.h"

namespace secondary_skill {

enum class Type : char { AIR_MAGIC, FIRE_MAGIC, EARTH_MAGIC, WATER_MAGIC };

enum class Level : char { BASIC = 0, ADVANCED = 1, EXPERT = 2 };

}  // namespace secondary_skill

class SecondarySkill : public IPrintable {
 private:
  // TODO zrobic fabryke
  secondary_skill::Type type_;
  secondary_skill::Level level_;
  uint32_t cost_;

  SecondarySkill( secondary_skill::Type skill_type );
  SecondarySkill( secondary_skill::Type skill_type, secondary_skill::Level skill_level );

 public:
  static std::unique_ptr<SecondarySkill> create( secondary_skill::Type type, secondary_skill::Level level );
  static std::unique_ptr<SecondarySkill> create( secondary_skill::Type type );

  void accept( Visitor& vis ) const override;
  [[nodiscard]] secondary_skill::Type getType() const;
  [[nodiscard]] secondary_skill::Level getLevel() const;
  [[nodiscard]] std::unique_ptr<SecondarySkill> copy() const;
};

// class AirMagic : public SecondarySkill {};
// class EarthMagic : public SecondarySkill {};
// class FireMagic : public SecondarySkill {};
// class WaterMagic : public SecondarySkill {};
// class Wisdom : public SecondarySkill {};
