#include "Character/CharacterInventory.h"

#include <algorithm>
#include <cstddef>
#include <numeric>
#include <optional>

#include "Artifact/Artifact.h"
#include "Artifact/ArtifactLib.h"
#include "Exceptions/EmptySlotException.hpp"
#include "Exceptions/Err.hpp"
#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Exceptions/NotEmptySlotException.hpp"

[[nodiscard]] bool CharacterInventory::isSlotEmpty( EquipmentSlots slot ) const noexcept {
  return equipment_[static_cast<size_t>( slot )] == std::nullopt;
}

[[nodiscard]] const std::optional<Artifact>& CharacterInventory::getSlot( EquipmentSlots slot ) const noexcept {
  return equipment_[static_cast<size_t>( slot )];
}
[[nodiscard]] const Equipment& CharacterInventory::getEquipment() const noexcept {
  return equipment_;
}
[[nodiscard]] const Backpack& CharacterInventory::getBackpack() const noexcept {
  return backpack_;
}

void CharacterInventory::pickUpArtifact( Artifact artifact ) noexcept {
  backpack_.push_back( artifact );
}
void CharacterInventory::equipArtifact( ArtifactType artifact, EquipmentSlots slot ) {
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
void CharacterInventory::unequipArtifact( EquipmentSlots slot ) {
  auto slot_id = static_cast<size_t>( slot );
  if ( !equipment_[slot_id] ) {
    err::raise<EmptySlotException>( "" );
  }
  Artifact extracted = *equipment_[slot_id];
  equipment_[slot_id] = std::nullopt;
  backpack_.push_back( extracted );
}