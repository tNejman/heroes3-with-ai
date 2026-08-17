#include "Game/GameStateStack.h"

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

#include "Exceptions/Err.hpp"
#include "Game/IGameState.h"

GameStateStack::GameStateStack() {
  buf_.reserve( 10 );
}

[[nodiscard]] const IGameState& GameStateStack::nth( int i ) const noexcept {
  err::passCondOrAbort( i >= 0, "id can't be negative" );
  err::passCondOrAbort( static_cast<size_t>( i ) < buf_.size(), "index out of bounds" );
  return *( buf_[static_cast<size_t>( i )] );
}

[[nodiscard]] IGameState& GameStateStack::nth( int i ) noexcept {
  return const_cast<IGameState&>( std::as_const( *this ).nth( i ) );
}

[[nodiscard]] const IGameState& GameStateStack::top() const noexcept {
  err::passCondOrAbort( !this->empty(), "tried getting from empty buf" );
  return *( buf_[buf_.size() - 1] );
}

[[nodiscard]] IGameState& GameStateStack::top() noexcept {
  return const_cast<IGameState&>( std::as_const( *this ).top() );
}

void GameStateStack::push( std::unique_ptr<IGameState> new_state ) noexcept {
  buf_.push_back( std::move( new_state ) );
}

void GameStateStack::pop() noexcept {
  err::passCondOrAbort( !buf_.empty(), "tried popping from empty" );
  buf_.pop_back();
}

[[nodiscard]] bool GameStateStack::empty() const noexcept {
  return buf_.empty();
}