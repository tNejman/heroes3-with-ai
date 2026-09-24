#include <algorithm>
#include <cstddef>
#include <optional>

#include "aux/Err.hpp"
#include "core/Character/Army.h"
#include "core/Exceptions/NotEmptySlotException.hpp"
#include "core/Unit/UnitStack.h"

[[nodiscard]] int character::Army::getCurrentPartySize() const noexcept {
  return static_cast<int>(
      std::ranges::count_if( party_, []( const auto& maybe_unit ) { return maybe_unit != std::nullopt; } ) );
}

[[nodiscard]] const character::Army::Party& character::Army::getParty() const noexcept {
  return party_;
}
[[nodiscard]] character::Army::Party& character::Army::getParty() noexcept {
  return party_;
}

[[nodiscard]] const std::optional<UnitStack>& character::Army::getPartyMember( PartySlot slot ) const noexcept {
  return party_[static_cast<size_t>( slot )];
}

UnitStack& character::Army::recruitUnitStack( const UnitStack& stack, PartySlot slot ) {
  if ( getPartyMember( slot ) ) {
    err::raise<NotEmptySlotException>( "" );
  }
  party_[static_cast<size_t>( slot )] = stack;
  return party_[static_cast<size_t>( slot )].value();
}

UnitStack& character::Army::recruitUnitStack( const UnitStack& stack ) {
  auto* ptr = std::ranges::find_if( party_, []( const auto& pos ) { return pos == std::nullopt; } );
  if ( ptr == party_.end() ) {
    err::raise<NotEmptySlotException>();
  }
  *ptr = stack;
  return ptr->value();
}

[[nodiscard]] character::Army character::Army::copy() const noexcept {
  character::Army army_copy{};
  army_copy.party_ = this->party_;
  army_copy.war_machines_ = this->war_machines_;

  return army_copy;
}
