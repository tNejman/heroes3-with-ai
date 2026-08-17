#pragma once

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Exceptions/Err.hpp"
#include "Game/IGameState.h"

class GameStateStack {
 private:
  std::vector<std::unique_ptr<IGameState>> buf_;

 public:
  GameStateStack();

  [[nodiscard]] const IGameState& nth( int i ) const noexcept;
  [[nodiscard]] IGameState& nth( int i ) noexcept;

  [[nodiscard]] const IGameState& top() const noexcept;
  [[nodiscard]] IGameState& top() noexcept;

  void push( std::unique_ptr<IGameState> ) noexcept;
  void pop() noexcept;

  [[nodiscard]] bool empty() const noexcept;
};