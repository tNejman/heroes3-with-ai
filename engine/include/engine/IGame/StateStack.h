#pragma once

#include <memory>
#include <vector>

namespace game {

class IState;

class StateStack {
 private:
  std::vector<std::unique_ptr<game::IState>> buf_;

 public:
  StateStack();

  [[nodiscard]] const IState& nth( int i ) const noexcept;
  [[nodiscard]] IState& nth( int i ) noexcept;

  [[nodiscard]] const IState& top() const noexcept;
  [[nodiscard]] IState& top() noexcept;

  void push( std::unique_ptr<IState> ) noexcept;
  void pop() noexcept;

  [[nodiscard]] bool empty() const noexcept;
};

};  // namespace game