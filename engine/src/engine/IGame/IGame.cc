#include "engine/IGame/IGame.h"

#include "engine/IGame/StateStack.h"

[[nodiscard]] game::StateStack& game::IGame::getStateStack() noexcept {
  return state_stack_;
}
[[nodiscard]] const game::StateStack& game::IGame::getStateStack() const noexcept {
  return state_stack_;
}
[[nodiscard]] game::IState& game::IGame::getState() noexcept {
  return state_stack_.top();
}

void game::IGame::incrementActionsSinceStart() noexcept {
  ++actions_since_start_;
}
void game::IGame::incrementTickSinceStart() noexcept {
  ++ticks_since_start_;
}

[[nodiscard]] const game::IState& game::IGame::getState() const noexcept {
  return state_stack_.top();
}

[[nodiscard]] int game::IGame::getActionsSinceStart() const noexcept {
  return actions_since_start_;
}
[[nodiscard]] int game::IGame::getTicksSinceStart() const noexcept {
  return ticks_since_start_;
}