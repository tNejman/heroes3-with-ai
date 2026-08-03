#include "Character/CharacterArmy.h"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>

#include "Exceptions/Err.hpp"
#include "Exceptions/NotEmptySlotException.hpp"
#include "Unit/UnitStack.h"

[[nodiscard]] int CharacterArmy::getCurrentPartySize() const noexcept {
  return static_cast<int>(
      std::ranges::count_if( party_, []( const auto& maybe_unit ) { return maybe_unit != nullptr; } ) );
}

[[nodiscard]] const Party& CharacterArmy::getParty() const noexcept {
  return party_;
}
[[nodiscard]] Party& CharacterArmy::getParty() noexcept {
  return party_;
}

[[nodiscard]] const std::shared_ptr<UnitStack>& CharacterArmy::getPartyMember( PartySlot slot ) const noexcept {
  return party_[static_cast<size_t>( slot )];
}

void CharacterArmy::recruitUnitStack( std::shared_ptr<UnitStack> stack, PartySlot slot ) {
  if ( getPartyMember( slot ) ) {
    err::raise<NotEmptySlotException>( "" );
  }
  party_[static_cast<size_t>( slot )] = std::move( stack );
}

void CharacterArmy::recruitUnitStack( std::shared_ptr<UnitStack> stack ) {
  auto* ptr = std::ranges::find_if( party_, []( const auto& pos ) { return pos == nullptr; } );
  if ( ptr == party_.end() ) {
    err::raise<NotEmptySlotException>();
  }
  *ptr = std::move( stack );
}