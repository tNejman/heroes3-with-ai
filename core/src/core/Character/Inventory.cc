#include "core/Character/Inventory.h"

#include <algorithm>
#include <cstddef>
#include <optional>

#include "aux/Err.hpp"
#include "core/Artifact/Artifact.h"
#include "core/Artifact/ArtifactLib.h"
#include "core/Exceptions/EmptySlotException.hpp"
#include "core/Exceptions/InvalidArtifactTypeException.hpp"
#include "core/Exceptions/NotEmptySlotException.hpp"

[[nodiscard]] bool character::Inventory::isSlotEmpty( EquipmentSlots slot ) const noexcept {
  return equipment_[static_cast<size_t>( slot )] == std::nullopt;
}

[[nodiscard]] const std::optional<Artifact>& character::Inventory::getSlot( EquipmentSlots slot ) const noexcept {
  return equipment_[static_cast<size_t>( slot )];
}
[[nodiscard]] const character::Inventory::Equipment& character::Inventory::getEquipment() const noexcept {
  return equipment_;
}
[[nodiscard]] const character::Inventory::Backpack& character::Inventory::getBackpack() const noexcept {
  return backpack_;
}

void character::Inventory::pickUpArtifact( Artifact artifact ) noexcept {
  backpack_.push_back( artifact );
}
void character::Inventory::equipArtifact( artifact::Type artifact, EquipmentSlots slot ) {
  auto it =
      std::ranges::find_if( backpack_, [artifact]( const Artifact& art ) { return art.getData().type_ == artifact; } );
  if ( it == backpack_.end() ) {
    err::raise<InvalidArtifactTypeException>( "no such artifact in backpack" );
  }
  if ( !isSlotEmpty( slot ) ) {
    err::raise<NotEmptySlotException>();
  }
  Artifact artifact_extracted = *it;
  backpack_.erase( it );
  equipment_[static_cast<size_t>( slot )] = artifact_extracted;
}
void character::Inventory::unequipArtifact( EquipmentSlots slot ) {
  auto slot_id = static_cast<size_t>( slot );
  if ( !equipment_[slot_id] ) {
    err::raise<EmptySlotException>( "" );
  }
  Artifact extracted = *equipment_[slot_id];
  equipment_[slot_id] = std::nullopt;
  backpack_.push_back( extracted );
}

[[nodiscard]] int character::Inventory::getTotalAttackBonus() const noexcept {
  return getStatBonus<&artifact::Data::attack_>();
}
[[nodiscard]] int character::Inventory::getTotalDefenseBonus() const noexcept {
  return getStatBonus<&artifact::Data::defense_>();
}
[[nodiscard]] int character::Inventory::getTotalPowerBonus() const noexcept {
  return getStatBonus<&artifact::Data::power_>();
}
[[nodiscard]] int character::Inventory::getTotalKnowledgeBonus() const noexcept {
  return getStatBonus<&artifact::Data::knowledge_>();
}
[[nodiscard]] int character::Inventory::getTotalSpeedBonus() const noexcept {
  return getStatBonus<&artifact::Data::speed_>();
}

[[nodiscard]] character::Inventory character::Inventory::copy() const noexcept {
  character::Inventory inventory_copy{};
  inventory_copy.equipment_ = this->equipment_;
  inventory_copy.backpack_ = this->backpack_;

  return inventory_copy;
}