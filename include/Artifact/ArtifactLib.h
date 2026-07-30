#pragma once

#include <array>

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

struct DisableCopyMove {  // NOLINT(cppcoreguidelines-special-member-functions)
  DisableCopyMove() = default;
  DisableCopyMove( const DisableCopyMove& ) = delete;
  DisableCopyMove( DisableCopyMove&& ) = delete;
  bool operator==( const DisableCopyMove& ) const noexcept = default;
};

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
struct ArtifactData {
  // this object never changes, is copied or moved so const members are ok
  const ArtifactType type_ = ArtifactType::BOOTS_OF_SPEED;
  const EquipmentSlots slot_ = EquipmentSlots::FEET;
  const int attack_ = 0;
  const int defense_ = 0;
  const int power_ = 0;
  const int knowledge_ = 0;
  const int speed_ = 0;
  const int cost_ = 0;

  [[no_unique_address]] DisableCopyMove _no_copy_move{};

  bool operator==( const ArtifactData& other ) const noexcept = default;
};
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)

namespace artifact_lib {

constexpr inline std::array ARTIFACTS_PRESET = { ArtifactData{ .type_ = ArtifactType::CROWN_OF_THE_SUPREME_MAGI,
                                                               .slot_ = EquipmentSlots::HELMET,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 5,
                                                               .knowledge_ = 5,
                                                               .speed_ = 0,
                                                               .cost_ = 10'000 },

                                                 ArtifactData{ .type_ = ArtifactType::HELM_OF_THE_ALABASTER_UNICORN,
                                                               .slot_ = EquipmentSlots::HELMET,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 2,
                                                               .cost_ = 5'000 },

                                                 ArtifactData{ .type_ = ArtifactType::THUNDER_HELMET,
                                                               .slot_ = EquipmentSlots::HELMET,
                                                               .attack_ = 3,
                                                               .defense_ = 3,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 6'000 },

                                                 ArtifactData{ .type_ = ArtifactType::DRAGON_WING_TABARD,
                                                               .slot_ = EquipmentSlots::CAPE,
                                                               .attack_ = -1,
                                                               .defense_ = -1,
                                                               .power_ = -1,
                                                               .knowledge_ = -1,
                                                               .speed_ = -1,
                                                               .cost_ = 5'000 },

                                                 ArtifactData{ .type_ = ArtifactType::CAPE_OF_VELOCITY,
                                                               .slot_ = EquipmentSlots::CAPE,
                                                               .attack_ = -2,
                                                               .defense_ = -2,
                                                               .power_ = -2,
                                                               .knowledge_ = -2,
                                                               .speed_ = -2,
                                                               .cost_ = 8'000 },

                                                 ArtifactData{ .type_ = ArtifactType::NECKLACE_OF_DRAGONTEETH,
                                                               .slot_ = EquipmentSlots::NECKLACE,
                                                               .attack_ = -1,
                                                               .defense_ = -1,
                                                               .power_ = -1,
                                                               .knowledge_ = -1,
                                                               .speed_ = -1,
                                                               .cost_ = 3'000 },

                                                 ArtifactData{ .type_ = ArtifactType::CELESTIAL_NECKLACE_OF_BLISS,
                                                               .slot_ = EquipmentSlots::NECKLACE,
                                                               .attack_ = -2,
                                                               .defense_ = -2,
                                                               .power_ = -2,
                                                               .knowledge_ = -2,
                                                               .speed_ = -2,
                                                               .cost_ = -2 },

                                                 ArtifactData{ .type_ = ArtifactType::NECKLACE_OF_SWIFTNESS,
                                                               .slot_ = EquipmentSlots::NECKLACE,
                                                               .attack_ = -3,
                                                               .defense_ = -3,
                                                               .power_ = -3,
                                                               .knowledge_ = -3,
                                                               .speed_ = -3,
                                                               .cost_ = -3 },

                                                 ArtifactData{ .type_ = ArtifactType::CENTAURS_AXE,
                                                               .slot_ = EquipmentSlots::WEAPON,
                                                               .attack_ = 2,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 2'000 },

                                                 ArtifactData{ .type_ = ArtifactType::TITANS_GLADIUS,
                                                               .slot_ = EquipmentSlots::WEAPON,
                                                               .attack_ = 12,
                                                               .defense_ = -3,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 10'000 },

                                                 ArtifactData{ .type_ = ArtifactType::SWORD_OF_JUDGEMENT,
                                                               .slot_ = EquipmentSlots::WEAPON,
                                                               .attack_ = 5,
                                                               .defense_ = 5,
                                                               .power_ = 5,
                                                               .knowledge_ = 5,
                                                               .speed_ = 0,
                                                               .cost_ = 20'000 },

                                                 ArtifactData{ .type_ = ArtifactType::SHIELD_OF_THE_DWARVEN_LORDS,
                                                               .slot_ = EquipmentSlots::SHIELD,
                                                               .attack_ = 0,
                                                               .defense_ = 2,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 2'000 },

                                                 ArtifactData{ .type_ = ArtifactType::DRAGON_SCALE_SHIELD,
                                                               .slot_ = EquipmentSlots::SHIELD,
                                                               .attack_ = 3,
                                                               .defense_ = 3,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 6'000 },

                                                 ArtifactData{ .type_ = ArtifactType::SENTINELS_SHIELD,
                                                               .slot_ = EquipmentSlots::SHIELD,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 8'000 },

                                                 ArtifactData{ .type_ = ArtifactType::RIB_CAGE,
                                                               .slot_ = EquipmentSlots::TORSO,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 2,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 3'000 },

                                                 ArtifactData{ .type_ = ArtifactType::DRAGON_SCALE_ARMOR,
                                                               .slot_ = EquipmentSlots::TORSO,
                                                               .attack_ = 4,
                                                               .defense_ = 4,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 8'000 },

                                                 ArtifactData{ .type_ = ArtifactType::TITANS_CUIRASS,
                                                               .slot_ = EquipmentSlots::TORSO,
                                                               .attack_ = 6,
                                                               .defense_ = 6,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 12'000 },

                                                 ArtifactData{ .type_ = ArtifactType::QUIET_EYE_OF_THE_DRAGON,
                                                               .slot_ = EquipmentSlots::RING,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 5'000 },

                                                 ArtifactData{ .type_ = ArtifactType::EQUESTRIAN_GLOVES,
                                                               .slot_ = EquipmentSlots::RING,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 3'000 },

                                                 ArtifactData{ .type_ = ArtifactType::RING_OF_VITALITY,
                                                               .slot_ = EquipmentSlots::RING,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 4'000 },

                                                 ArtifactData{ .type_ = ArtifactType::RING_OF_WAYFARER,
                                                               .slot_ = EquipmentSlots::RING,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 3'000 },

                                                 ArtifactData{ .type_ = ArtifactType::RING_OF_LIFE,
                                                               .slot_ = EquipmentSlots::RING,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 6'000 },

                                                 ArtifactData{ .type_ = ArtifactType::DRAGONBONE_GREAVES,
                                                               .slot_ = EquipmentSlots::FEET,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 4'000 },

                                                 ArtifactData{ .type_ = ArtifactType::SANDALS_OF_THE_SAINT,
                                                               .slot_ = EquipmentSlots::FEET,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 5'000 },

                                                 ArtifactData{ .type_ = ArtifactType::BOOTS_OF_SPEED,
                                                               .slot_ = EquipmentSlots::FEET,
                                                               .attack_ = 0,
                                                               .defense_ = 0,
                                                               .power_ = 0,
                                                               .knowledge_ = 0,
                                                               .speed_ = 0,
                                                               .cost_ = 6'000 } };
}  // namespace artifact_lib