#pragma once

#include <memory>
#include <set>
#include <string>

#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Miscellaneous/ProjectLib.h"

enum class ArtifactType : int {
  // Helmets
  CROWN_OF_THE_SUPREME_MAGI,
  HELM_OF_THE_ALABASTER_UNICORN,
  THUNDER_HELMET,

  // Capes
  DRAGON_WING_TABARD,
  CAPE_OF_VELOCITY,

  // Necklaces
  NECKLACE_OF_DRAGONTEETH,
  CELESTIAL_NECKLACE_OF_BLISS,
  NECKLACE_OF_SWIFTNESS,

  // Weapons
  CENTAURS_AXE,
  TITANS_GLADIUS,
  SWORD_OF_JUDGEMENT,

  // Shields
  SHIELD_OF_THE_DWARVEN_LORDS,
  DRAGON_SCALE_SHIELD,
  SENTINELS_SHIELD,

  // Torsos
  RIB_CAGE,
  DRAGON_SCALE_ARMOR,
  TITANS_CUIRASS,

  // Rings
  QUIET_EYE_OF_THE_DRAGON,
  EQUESTRIAN_GLOVES,
  RING_OF_VITALITY,
  RING_OF_WAYFARER,
  RING_OF_LIFE,

  // Feet
  DRAGONBONE_GREAVES,
  SANDALS_OF_THE_SAINT,
  BOOTS_OF_SPEED,

  // Misc
};

class ArtifactData {
 public:
  const ArtifactType type_;
  const EquipmentSlots slot_;
  const std::string name_;
  const int attack_;
  const int defense_;
  const int power_;
  const int knowledge_;
  const int speed_;
  const uint32_t cost_;

  ArtifactData(
      const ArtifactType type,
      const EquipmentSlots slot,
      const std::string& name,
      const int attack,
      const int defense,
      const int power,
      const int knowledge,
      const int speed,
      const uint32_t cost ) : type_( type ),
                              slot_( slot ),
                              name_( name ),
                              attack_( attack ),
                              defense_( defense ),
                              power_( power ),
                              knowledge_( knowledge ),
                              speed_( speed ),
                              cost_( cost ) {};
};

const std::set<std::shared_ptr<const ArtifactData>> ARTIFACTS_PRESET = {
    std::make_shared<ArtifactData>( ArtifactType::CROWN_OF_THE_SUPREME_MAGI,
                                    EquipmentSlots::HELMET, "crown_of_the_supreme_magi", 0, 0, 5, 5, 0, 10'000u ),
    std::make_shared<ArtifactData>( ArtifactType::HELM_OF_THE_ALABASTER_UNICORN,
                                    EquipmentSlots::HELMET, "helm_of_the_alabaster_unicorn", 0, 0, 0, 0, 2, 5'000u ),
    std::make_shared<ArtifactData>( ArtifactType::THUNDER_HELMET,
                                    EquipmentSlots::HELMET, "thunder_helmet", 3, 3, 0, 0, 0, 6'000u ),

    std::make_shared<ArtifactData>( ArtifactType::DRAGON_WING_TABARD,
                                    EquipmentSlots::CAPE, "dragon_wing_tabard", -1, -1, -1, -1, -1, 5'000u ),
    std::make_shared<ArtifactData>( ArtifactType::CAPE_OF_VELOCITY,
                                    EquipmentSlots::CAPE, "cape_of_velocity", -2, -2, -2, -2, -2, 8'000u ),

    std::make_shared<ArtifactData>( ArtifactType::NECKLACE_OF_DRAGONTEETH,
                                    EquipmentSlots::NECKLACE, "necklace_of_dragonteeth", -1, -1, -1, -1, -1, 3'000u ),
    std::make_shared<ArtifactData>( ArtifactType::CELESTIAL_NECKLACE_OF_BLISS,
                                    EquipmentSlots::NECKLACE, "celestial_necklace_of_bliss", -2, -2, -2, -2, -2, -2 ),
    std::make_shared<ArtifactData>( ArtifactType::NECKLACE_OF_SWIFTNESS,
                                    EquipmentSlots::NECKLACE, "necklace_of_swiftness", -3, -3, -3, -3, -3, -3 ),

    std::make_shared<ArtifactData>( ArtifactType::CENTAURS_AXE,
                                    EquipmentSlots::WEAPON, "centaurs_axe", 2, 0, 0, 0, 0, 2'000u ),
    std::make_shared<ArtifactData>( ArtifactType::TITANS_GLADIUS,
                                    EquipmentSlots::WEAPON, "titans_gladius", 12, -3, 0, 0, 0, 10'000u ),
    std::make_shared<ArtifactData>( ArtifactType::SWORD_OF_JUDGEMENT,
                                    EquipmentSlots::WEAPON, "sword_of_judgement", 5, 5, 5, 5, 0, 20'000u ),

    std::make_shared<ArtifactData>( ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS,
                                    EquipmentSlots::SHIELD, "shield_of_the_dwarven_lords", 0, 2, 0, 0, 0, 2'000u ),
    std::make_shared<ArtifactData>( ArtifactType::DRAGON_SCALE_SHIELD,
                                    EquipmentSlots::SHIELD, "dragon_scale_shield", 3, 3, 0, 0, 0, 6'000u ),
    std::make_shared<ArtifactData>( ArtifactType::SENTINELS_SHIELD,
                                    EquipmentSlots::SHIELD, "sentinels_shield", 0, 0, 0, 0, 0, 8'000u ),

    std::make_shared<ArtifactData>( ArtifactType::RIB_CAGE,
                                    EquipmentSlots::TORSO, "rib_cage", 0, 0, 2, 0, 0, 3'000u ),
    std::make_shared<ArtifactData>( ArtifactType::DRAGON_SCALE_ARMOR,
                                    EquipmentSlots::TORSO, "dragon_scale_armor", 4, 4, 0, 0, 0, 8'000u ),
    std::make_shared<ArtifactData>( ArtifactType::TITANS_CUIRASS,
                                    EquipmentSlots::TORSO, "titans_cuirass", 6, 6, 0, 0, 0, 12'000u ),

    std::make_shared<ArtifactData>( ArtifactType::QUIET_EYE_OF_THE_DRAGON,
                                    EquipmentSlots::RING, "quiet_eye_of_the_dragon", 0, 0, 0, 0, 0, 5'000u ),
    std::make_shared<ArtifactData>( ArtifactType::EQUESTRIAN_GLOVES,
                                    EquipmentSlots::RING, "equestrian_gloves", 0, 0, 0, 0, 0, 3'000u ),
    std::make_shared<ArtifactData>( ArtifactType::RING_OF_VITALITY,
                                    EquipmentSlots::RING, "ring_of_vitality", 0, 0, 0, 0, 0, 4'000u ),
    std::make_shared<ArtifactData>( ArtifactType::RING_OF_WAYFARER,
                                    EquipmentSlots::RING, "ring_of_wayfarer", 0, 0, 0, 0, 0, 3'000u ),
    std::make_shared<ArtifactData>( ArtifactType::RING_OF_LIFE,
                                    EquipmentSlots::RING, "ring_of_life", 0, 0, 0, 0, 0, 6'000u ),

    std::make_shared<ArtifactData>( ArtifactType::DRAGONBONE_GREAVES,
                                    EquipmentSlots::FEET, "dragonbone_greaves", 0, 0, 0, 0, 0, 4'000u ),
    std::make_shared<ArtifactData>( ArtifactType::SANDALS_OF_THE_SAINT,
                                    EquipmentSlots::FEET, "sandals_of_the_saint", 0, 0, 0, 0, 0, 5'000u ),
    std::make_shared<ArtifactData>( ArtifactType::BOOTS_OF_SPEED,
                                    EquipmentSlots::FEET, "boots_of_speed", 0, 0, 0, 0, 0, 6'000u ) };