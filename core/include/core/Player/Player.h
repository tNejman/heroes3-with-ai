#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Player:
    - klasa pozwala na zarządzanie graczem
    - Jest też Interfejsem do zarządzania ruchami AI i człowieka
*/

#include <array>
#include <cstdint>
#include <memory>
#include <vector>

#include <magic_enum/magic_enum.hpp>

#include "core/Character/Character.h"
#include "core/Misc/ProjectLib.h"
#include "core/Resource/Resource.h"
#include "core/WorldMap/Castles/Castle.h"


class Move;

enum PlayerColor : uint8_t { RED, BLUE, TAN, GREEN, ORANGE, PURPLE, TEAL, PINK, COUNT };

// inheritance from Printable is postponed for now
class Player {
 private:
  std::vector<std::shared_ptr<Character>> characters_on_map_;
  std::vector<std::weak_ptr<Castle>> owned_castles_;
  std::array<std::unique_ptr<Resource>, magic_enum::enum_count<Resource::Type>()> resources_;

  PlayerColor color_;

 public:
  [[nodiscard]] Player( std::vector<std::shared_ptr<Character>> characters ) : characters_on_map_( characters ) {
  }
  ~Player() = default;

  [[nodiscard]] std::vector<std::shared_ptr<Character>>& getCharacters() noexcept;
  [[nodiscard]] const std::vector<std::shared_ptr<Character>>& getCharacters() const noexcept;

  // below are not implemented
  [[nodiscard]] bool addCharacter( std::shared_ptr<Character> character ) noexcept;
  void addCastle( std::shared_ptr<Castle> castle ) noexcept;
  [[nodiscard]] std::shared_ptr<Castle> getCastles() noexcept;
  [[nodiscard]] bool deleteCharacter( std::shared_ptr<Character> character ) noexcept;
  [[nodiscard]] bool loseCastle( std::shared_ptr<Castle> castle ) noexcept;
  [[nodiscard]] std::array<std::shared_ptr<Resource>, AMOUNT_OF_RESOURCES> getResourcesInPointers() noexcept;
  [[nodiscard]] std::array<Resource, AMOUNT_OF_RESOURCES> getResourcesInValues() noexcept;
  [[nodiscard]] Resource getResource( Resource::Type resource ) const noexcept;
  [[nodiscard]] Resource setResource( Resource::Type resource, int amount ) noexcept;
  [[nodiscard]] std::shared_ptr<Move> makeMove( std::vector<Move> possible_states ) noexcept;

  [[nodiscard]] PlayerColor getColor() const noexcept;
};