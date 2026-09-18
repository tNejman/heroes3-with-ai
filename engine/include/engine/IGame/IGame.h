#pragma once

#include "engine/IGame/StateStack.h"

namespace game {

class IGame {  // NOLINT(cppcoreguidelines-special-member-functions)
 private:
  StateStack state_stack_;

  int actions_since_start_ = 0;
  int ticks_since_start_ = 0;

 protected:
  IGame() = default;

  [[nodiscard]] StateStack& getStateStack() noexcept;
  [[nodiscard]] const StateStack& getStateStack() const noexcept;
  [[nodiscard]] IState& getState() noexcept;

  void incrementActionsSinceStart() noexcept;
  void incrementTickSinceStart() noexcept;

 public:
  virtual ~IGame() = default;

  [[nodiscard]] const IState& getState() const noexcept;

  [[nodiscard]] int getActionsSinceStart() const noexcept;
  [[nodiscard]] int getTicksSinceStart() const noexcept;
};

};  // namespace game