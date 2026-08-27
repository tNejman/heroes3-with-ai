#pragma once

// Author: Tomasz Nejman
/* content:
    - module for class 'Character' containing army
*/

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>

#include "Unit/UnitStack.h"
#include "Unit/UnitsLib.h"

constexpr inline int MAX_PARTY_SIZE = 7;

enum class PartySlot : char {  // do not change numeration
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN
};

using Party = std::array<std::optional<UnitStack>, MAX_PARTY_SIZE>;
using WarMachineArr = std::array<std::optional<UnitStack>, static_cast<size_t>( WarMachineType::COUNT )>;

class CharacterArmy {
 private:
  Party party_;
  WarMachineArr war_machines_;

 public:
  CharacterArmy() = default;
  CharacterArmy( const CharacterArmy& ) = delete;
  CharacterArmy( CharacterArmy&& ) = delete;
  ~CharacterArmy() = default;
  CharacterArmy& operator=( const CharacterArmy& ) = delete;
  CharacterArmy& operator=( CharacterArmy&& ) = delete;

  [[nodiscard]] int getCurrentPartySize() const noexcept;
  [[nodiscard]] const Party& getParty() const noexcept;
  [[nodiscard]] Party& getParty() noexcept;
  [[nodiscard]] const std::optional<UnitStack>& getPartyMember( PartySlot slot ) const noexcept;
  UnitStack& recruitUnitStack( const UnitStack& stack, PartySlot slot );
  UnitStack& recruitUnitStack( const UnitStack& stack );

  /* ideas @TODO
    - recruit and unrecruit war machines
    - change war machine storage style
    - auto recruit unit into empty slot
    -
  */
};