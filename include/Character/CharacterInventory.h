#pragma once

#include <array>
#include <cstddef>
#include <optional>
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
  bool equipArtifact( ArtifactType artifact, EquipmentSlots slot ) noexcept;  // maybe?
  bool unequipArtifact( EquipmentSlots slot ) noexcept;

  [[nodiscard]] int getTotalAttackBonus() const noexcept;
  [[nodiscard]] int getTotalDefenseBonus() const noexcept;
  [[nodiscard]] int getTotalPowerBonus() const noexcept;
  [[nodiscard]] int getTotalKnowledgeBonus() const noexcept;
  [[nodiscard]] int getTotalSpeedBonus() const noexcept;
};