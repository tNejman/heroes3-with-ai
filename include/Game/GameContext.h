#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "Character/Character.h"
#include "Player/Player.h"
class GameContext {
 private:
  std::vector<std::shared_ptr<Player>> players_;
  std::reference_wrapper<Player> current_player_;
  std::reference_wrapper<Character> current_character_;

 public:
  GameContext( std::vector<std::shared_ptr<Player>>&& ) noexcept;

  [[nodiscard]] const std::vector<std::shared_ptr<Player>>& getPlayers() const noexcept;
  [[nodiscard]] std::vector<std::shared_ptr<Player>>& getPlayers() noexcept;

  [[nodiscard]] std::shared_ptr<Character> findCharacterById( int id ) const noexcept;
  [[nodiscard]] std::shared_ptr<Character> findCharacterById( int id ) noexcept;

  [[nodiscard]] const Player& getCurrentPlayer() const noexcept;
  [[nodiscard]] Player& getCurrentPlayer() noexcept;

  [[nodiscard]] const Character& getCurrentCharacter() const noexcept;
  [[nodiscard]] Character& getCurrentCharacter() noexcept;

  Player& nextPlayer() noexcept;
  Character& nextCharacter() noexcept;
};