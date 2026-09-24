#pragma once

#include <array>
#include <cstddef>
#include <magic_enum/magic_enum.hpp>

#include "aux/DisableCopyMoveStructHelper.hpp"

enum class EquipmentSlots : char {
  HELMET = 0,
  CAPE = 1,
  NECKLACE = 2,
  WEAPON = 3,
  SHIELD = 4,
  TORSO = 5,
  RING = 6,
  RING_1 = 7,
  RING_2 = 8,
  FEET = 9,
  MISC = 10,
  MISC_1 = 10,
  MISC_2 = 11,
  MISC_3 = 12,
  MISC_4 = 13,
  MISC_5 = 14,
};

namespace artifact {

enum class Type : char {
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

// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)
struct Data {
  const artifact::Type type_;
  const EquipmentSlots slot_;
  const int attack_;
  const int defense_;
  const int power_;
  const int knowledge_;
  const int speed_;
  const int cost_;

  [[no_unique_address]] DisableCopyMove _no_copy_move{};

  bool operator==( const artifact::Data& other ) const noexcept = default;
};
// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members,misc-non-private-member-variables-in-classes)

constexpr inline std::array PRESET = { artifact::Data{ .type_ = artifact::Type::CROWN_OF_THE_SUPREME_MAGI,
                                                       .slot_ = EquipmentSlots::HELMET,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 5,
                                                       .knowledge_ = 5,
                                                       .speed_ = 0,
                                                       .cost_ = 10'000 },

                                       artifact::Data{ .type_ = artifact::Type::HELM_OF_THE_ALABASTER_UNICORN,
                                                       .slot_ = EquipmentSlots::HELMET,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 2,
                                                       .cost_ = 5'000 },

                                       artifact::Data{ .type_ = artifact::Type::THUNDER_HELMET,
                                                       .slot_ = EquipmentSlots::HELMET,
                                                       .attack_ = 3,
                                                       .defense_ = 3,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 6'000 },

                                       artifact::Data{ .type_ = artifact::Type::DRAGON_WING_TABARD,
                                                       .slot_ = EquipmentSlots::CAPE,
                                                       .attack_ = -1,
                                                       .defense_ = -1,
                                                       .power_ = -1,
                                                       .knowledge_ = -1,
                                                       .speed_ = -1,
                                                       .cost_ = 5'000 },

                                       artifact::Data{ .type_ = artifact::Type::CAPE_OF_VELOCITY,
                                                       .slot_ = EquipmentSlots::CAPE,
                                                       .attack_ = -2,
                                                       .defense_ = -2,
                                                       .power_ = -2,
                                                       .knowledge_ = -2,
                                                       .speed_ = -2,
                                                       .cost_ = 8'000 },

                                       artifact::Data{ .type_ = artifact::Type::NECKLACE_OF_DRAGONTEETH,
                                                       .slot_ = EquipmentSlots::NECKLACE,
                                                       .attack_ = -1,
                                                       .defense_ = -1,
                                                       .power_ = -1,
                                                       .knowledge_ = -1,
                                                       .speed_ = -1,
                                                       .cost_ = 3'000 },

                                       artifact::Data{ .type_ = artifact::Type::CELESTIAL_NECKLACE_OF_BLISS,
                                                       .slot_ = EquipmentSlots::NECKLACE,
                                                       .attack_ = -2,
                                                       .defense_ = -2,
                                                       .power_ = -2,
                                                       .knowledge_ = -2,
                                                       .speed_ = -2,
                                                       .cost_ = -2 },

                                       artifact::Data{ .type_ = artifact::Type::NECKLACE_OF_SWIFTNESS,
                                                       .slot_ = EquipmentSlots::NECKLACE,
                                                       .attack_ = -3,
                                                       .defense_ = -3,
                                                       .power_ = -3,
                                                       .knowledge_ = -3,
                                                       .speed_ = -3,
                                                       .cost_ = -3 },

                                       artifact::Data{ .type_ = artifact::Type::CENTAURS_AXE,
                                                       .slot_ = EquipmentSlots::WEAPON,
                                                       .attack_ = 2,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 2'000 },

                                       artifact::Data{ .type_ = artifact::Type::TITANS_GLADIUS,
                                                       .slot_ = EquipmentSlots::WEAPON,
                                                       .attack_ = 12,
                                                       .defense_ = -3,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 10'000 },

                                       artifact::Data{ .type_ = artifact::Type::SWORD_OF_JUDGEMENT,
                                                       .slot_ = EquipmentSlots::WEAPON,
                                                       .attack_ = 5,
                                                       .defense_ = 5,
                                                       .power_ = 5,
                                                       .knowledge_ = 5,
                                                       .speed_ = 0,
                                                       .cost_ = 20'000 },

                                       artifact::Data{ .type_ = artifact::Type::SHIELD_OF_THE_DWARVEN_LORDS,
                                                       .slot_ = EquipmentSlots::SHIELD,
                                                       .attack_ = 0,
                                                       .defense_ = 2,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 2'000 },

                                       artifact::Data{ .type_ = artifact::Type::DRAGON_SCALE_SHIELD,
                                                       .slot_ = EquipmentSlots::SHIELD,
                                                       .attack_ = 3,
                                                       .defense_ = 3,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 6'000 },

                                       artifact::Data{ .type_ = artifact::Type::SENTINELS_SHIELD,
                                                       .slot_ = EquipmentSlots::SHIELD,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 8'000 },

                                       artifact::Data{ .type_ = artifact::Type::RIB_CAGE,
                                                       .slot_ = EquipmentSlots::TORSO,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 2,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 3'000 },

                                       artifact::Data{ .type_ = artifact::Type::DRAGON_SCALE_ARMOR,
                                                       .slot_ = EquipmentSlots::TORSO,
                                                       .attack_ = 4,
                                                       .defense_ = 4,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 8'000 },

                                       artifact::Data{ .type_ = artifact::Type::TITANS_CUIRASS,
                                                       .slot_ = EquipmentSlots::TORSO,
                                                       .attack_ = 6,
                                                       .defense_ = 6,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 12'000 },

                                       artifact::Data{ .type_ = artifact::Type::QUIET_EYE_OF_THE_DRAGON,
                                                       .slot_ = EquipmentSlots::RING,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 5'000 },

                                       artifact::Data{ .type_ = artifact::Type::EQUESTRIAN_GLOVES,
                                                       .slot_ = EquipmentSlots::RING,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 3'000 },

                                       artifact::Data{ .type_ = artifact::Type::RING_OF_VITALITY,
                                                       .slot_ = EquipmentSlots::RING,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 4'000 },

                                       artifact::Data{ .type_ = artifact::Type::RING_OF_WAYFARER,
                                                       .slot_ = EquipmentSlots::RING,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 3'000 },

                                       artifact::Data{ .type_ = artifact::Type::RING_OF_LIFE,
                                                       .slot_ = EquipmentSlots::RING,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 6'000 },

                                       artifact::Data{ .type_ = artifact::Type::DRAGONBONE_GREAVES,
                                                       .slot_ = EquipmentSlots::FEET,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 4'000 },

                                       artifact::Data{ .type_ = artifact::Type::SANDALS_OF_THE_SAINT,
                                                       .slot_ = EquipmentSlots::FEET,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 5'000 },

                                       artifact::Data{ .type_ = artifact::Type::BOOTS_OF_SPEED,
                                                       .slot_ = EquipmentSlots::FEET,
                                                       .attack_ = 0,
                                                       .defense_ = 0,
                                                       .power_ = 0,
                                                       .knowledge_ = 0,
                                                       .speed_ = 0,
                                                       .cost_ = 6'000 } };
}  // namespace artifact

consteval bool areAllArtifactsPreset() {
  if ( artifact::PRESET.size() != magic_enum::enum_count<artifact::Type>() ) {
    return false;
  }

  for ( size_t i = 0; i < artifact::PRESET.size(); ++i ) {
    if ( artifact::PRESET[i].type_ != static_cast<artifact::Type>( i ) ) {
      return false;
    }
  }
  return true;
}

static_assert( areAllArtifactsPreset() );