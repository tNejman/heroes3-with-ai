#include "engine/IGame/StateStack.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

#include "aux/Err.hpp"
#include "core/Game/IState.h"

constexpr inline size_t ASSUMED_SAFE_MAX_STATE_COUNT = 10;

namespace game {

game::StateStack::StateStack() {
  buf_.reserve( ASSUMED_SAFE_MAX_STATE_COUNT );
}

[[nodiscard]] const IState& StateStack::nth( int i ) const noexcept {
  err::passCondOrAbort( i >= 0, "id can't be negative" );
  err::passCondOrAbort( static_cast<size_t>( i ) < buf_.size(), "index out of bounds" );
  return *( buf_[static_cast<size_t>( i )] );
}

[[nodiscard]] IState& StateStack::nth( int i ) noexcept {
  // this is ok, just to not duplicate code in const and non-const methods
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  return const_cast<IState&>( std::as_const( *this ).nth( i ) );
}

[[nodiscard]] const IState& StateStack::top() const noexcept {
  err::passCondOrAbort( !this->empty(), "tried getting from empty buf" );
  return *( buf_.back() );
}

[[nodiscard]] IState& StateStack::top() noexcept {
  // this is ok, just to not duplicate code in const and non-const methods
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
  return const_cast<IState&>( std::as_const( *this ).top() );
}

void StateStack::push( std::unique_ptr<IState> new_state ) noexcept {
  buf_.push_back( std::move( new_state ) );
}

void StateStack::pop() noexcept {
  err::passCondOrAbort( !buf_.empty(), "tried popping from empty" );
  buf_.pop_back();
}

[[nodiscard]] bool StateStack::empty() const noexcept {
  return buf_.empty();
}

}  // namespace game