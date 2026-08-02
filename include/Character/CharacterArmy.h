#pragma once

// Author: Tomasz Nejman
/* content:
    - module for class 'Character' containing army
*/

#include <array>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "Graphics/Visitor.h"
#include "Unit/UnitStack.h"

constexpr inline int MAX_PARTY_SIZE = 7;

enum class PartySlot : uint8_t {  // do not change numeration
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN
};

using Party = std::array<std::optional<UnitStack>, MAX_PARTY_SIZE>;

class CharacterArmy {
 private:
  Party party_;
  std::map<std::string, std::shared_ptr<WarMachine>> war_machines_;

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
  void recruitUnitStack( UnitStack stack, PartySlot slot );
  void recruitUnitStack( UnitStack stack );

  /* ideas @TODO
    - recruit and unrecruit war machines
    - change war machine storage style
    - auto recruit unit into empty slot
    -
  */
};