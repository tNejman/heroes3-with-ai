#pragma once

#include <array>
#include <cstddef>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "Artifact/Artifact.h"
#include "Artifact/ArtifactLib.h"

constexpr inline std::size_t EQUIPMENT_SLOTS_COUNT = std::to_underlying( EquipmentSlots::COUNT );

using Equipment = std::array<std::optional<Artifact>, EQUIPMENT_SLOTS_COUNT>;
using Backpack = std::vector<Artifact>;

class CharacterInventory {
 private:
  Equipment equipment_;
  Backpack backpack_;

 public:
  CharacterInventory() = default;
  CharacterInventory( const CharacterInventory& ) = delete;
  CharacterInventory( CharacterInventory&& ) = delete;
  ~CharacterInventory() = default;
  CharacterInventory& operator=( const CharacterInventory& ) = delete;
  CharacterInventory& operator=( CharacterInventory&& ) = delete;

  [[nodiscard]] bool isSlotEmpty( EquipmentSlots slot ) const noexcept;
  [[nodiscard]] const std::optional<Artifact>& getSlot( EquipmentSlots slot ) const noexcept;
  [[nodiscard]] const Equipment& getEquipment() const noexcept;
  [[nodiscard]] const Backpack& getBackpack() const noexcept;

  void pickUpArtifact( Artifact artifact ) noexcept;
  void equipArtifact( ArtifactType artifact, EquipmentSlots slot );
  void unequipArtifact( EquipmentSlots slot );

  template <auto Member>
  requires std::is_member_object_pointer_v<decltype( Member )> && requires( ArtifactData a ) { a.*Member; }
  [[nodiscard]] int getStatBonus() const noexcept {
    int stat_bonus = 0;
    for ( const auto& artifact : equipment_ ) {
      if ( !artifact ) {
        continue;
      }
      stat_bonus += artifact->getData().*Member;
    }
    return stat_bonus;
  }

  [[nodiscard]] int getTotalAttackBonus() const noexcept {
    return getStatBonus<&ArtifactData::attack_>();
  }
  [[nodiscard]] int getTotalDefenseBonus() const noexcept {
    return getStatBonus<&ArtifactData::defense_>();
  }
  [[nodiscard]] int getTotalPowerBonus() const noexcept {
    return getStatBonus<&ArtifactData::power_>();
  }
  [[nodiscard]] int getTotalKnowledgeBonus() const noexcept {
    return getStatBonus<&ArtifactData::knowledge_>();
  }
  [[nodiscard]] int getTotalSpeedBonus() const noexcept {
    return getStatBonus<&ArtifactData::speed_>();
  }
};