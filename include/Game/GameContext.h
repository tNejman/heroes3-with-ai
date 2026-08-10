#pragma once

#include <memory>
#include <vector>

#include "Character/Character.h"
#include "Player/Player.h"
class GameContext {
 private:
  std::vector<std::shared_ptr<Player>> players_;

 public:
  GameContext( std::vector<std::shared_ptr<Player>>&& ) noexcept;

  [[nodiscard]] const std::vector<std::shared_ptr<Player>>& getPlayers() const noexcept;
  [[nodiscard]] std::vector<std::shared_ptr<Player>>& getPlayers() noexcept;

  [[nodiscard]] std::shared_ptr<Character> findCharacterById( int id ) const noexcept;
  [[nodiscard]] std::shared_ptr<Character> findCharacterById( int id ) noexcept;
};