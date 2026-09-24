#pragma once

#include <array>
#include <cstddef>
#include <magic_enum/magic_enum.hpp>
#include <optional>
#include <type_traits>
#include <vector>

#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"

namespace character {

constexpr inline std::size_t EQUIPMENT_SLOTS_COUNT = magic_enum::enum_count<EquipmentSlots>();

class Inventory {
 public:
  using Equipment = std::array<std::optional<Artifact>, EQUIPMENT_SLOTS_COUNT>;
  using Backpack = std::vector<Artifact>;

 private:
  Equipment equipment_;
  Backpack backpack_;

  template <auto Member>
  requires std::is_member_object_pointer_v<decltype( Member )> && requires( artifact::Data a ) { a.*Member; }
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

 public:
  Inventory() = default;
  Inventory( const Inventory& ) = delete;
  Inventory( Inventory&& ) = default;
  ~Inventory() = default;
  Inventory& operator=( const Inventory& ) = delete;
  Inventory& operator=( Inventory&& ) = default;

  [[nodiscard]] bool isSlotEmpty( EquipmentSlots slot ) const noexcept;
  [[nodiscard]] const std::optional<Artifact>& getSlot( EquipmentSlots slot ) const noexcept;
  [[nodiscard]] const Equipment& getEquipment() const noexcept;
  [[nodiscard]] const Backpack& getBackpack() const noexcept;

  void pickUpArtifact( Artifact artifact ) noexcept;
  void equipArtifact( artifact::Type artifact, EquipmentSlots slot );
  void unequipArtifact( EquipmentSlots slot );

  [[nodiscard]] int getTotalAttackBonus() const noexcept;
  [[nodiscard]] int getTotalDefenseBonus() const noexcept;
  [[nodiscard]] int getTotalPowerBonus() const noexcept;
  [[nodiscard]] int getTotalKnowledgeBonus() const noexcept;
  [[nodiscard]] int getTotalSpeedBonus() const noexcept;

  [[nodiscard]] Inventory copy() const noexcept;
};

}  // namespace character