#pragma once

// Author: Tomasz Nejman
/* content:
    - module for class 'Character' containing army
*/

#include <array>
#include <cstddef>
#include <magic_enum/magic_enum.hpp>
#include <optional>

#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"

namespace character {

constexpr inline int MAX_PARTY_SIZE = 7;
constexpr inline int WAR_MACHINE_SLOT_COUNT = static_cast<size_t>( magic_enum::enum_count<WarMachineType>() );

enum class PartySlot : char {  // do not change numeration
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN
};

class Army {
 public:
  using Party = std::array<std::optional<UnitStack>, MAX_PARTY_SIZE>;
  using WarMachineArr = std::array<std::optional<UnitStack>, WAR_MACHINE_SLOT_COUNT>;

 private:
  Party party_;
  WarMachineArr war_machines_;

 public:
  Army() = default;
  Army( const Army& ) = delete;
  Army( Army&& ) = default;
  ~Army() = default;
  Army& operator=( const Army& ) = delete;
  Army& operator=( Army&& ) = default;

  [[nodiscard]] int getCurrentPartySize() const noexcept;
  [[nodiscard]] const Party& getParty() const noexcept;
  [[nodiscard]] Party& getParty() noexcept;
  [[nodiscard]] const std::optional<UnitStack>& getPartyMember( PartySlot slot ) const noexcept;
  [[nodiscard]] const std::optional<UnitStack>& getWarMachine( WarMachineType slot ) const noexcept;
  UnitStack& recruitUnitStack( const UnitStack& stack, PartySlot slot );
  UnitStack& recruitUnitStack( const UnitStack& stack );

  [[nodiscard]] bool containsInParty( const UnitStack& stack ) const noexcept;

  [[nodiscard]] Army copy() const noexcept;

  /* ideas @TODO
    - recruit and unrecruit war machines
    - change war machine storage style
    - auto recruit unit into empty slot
    -
  */
};

}  // namespace character