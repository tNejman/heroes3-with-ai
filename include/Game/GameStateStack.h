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

  [[nodiscard]] const IGameState& nth( int i ) const;
  [[nodiscard]] IGameState& nth( int i );

  [[nodiscard]] const IGameState& top() const;
  [[nodiscard]] IGameState& top();

  void push( std::unique_ptr<IGameState> );
  void pop();

    [[nodiscard]] bool empty() const noexcept;
};