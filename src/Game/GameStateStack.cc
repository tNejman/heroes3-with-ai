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

[[nodiscard]] const IGameState& GameStateStack::nth( int i ) const {
  if ( i < 0 ) {
    err::raise<std::runtime_error>( "id can't be negative" );
  }
  if ( static_cast<size_t>( i ) >= buf_.size() ) {
    err::raise<std::runtime_error>( "index out of bounds" );
  }
  return *( buf_[static_cast<size_t>( i )] );
}

[[nodiscard]] IGameState& GameStateStack::nth( int i ) {
  return const_cast<IGameState&>( std::as_const( *this ).nth( i ) );
}

[[nodiscard]] const IGameState& GameStateStack::top() const {
  if ( buf_.empty() ) {
    err::raise<std::runtime_error>( "tried getting from empty buf" );
  }
  return *( buf_[buf_.size() - 1] );
}

[[nodiscard]] IGameState& GameStateStack::top() {
  return const_cast<IGameState&>( std::as_const( *this ).top() );
}

void GameStateStack::push( std::unique_ptr<IGameState> new_state ) {
  buf_.push_back( std::move( new_state ) );
}

void GameStateStack::pop() {
  if ( buf_.empty() ) {
    err::raise<std::runtime_error>( "tried popping from empty" );
  }
  buf_.pop_back();
}

[[nodiscard]] bool GameStateStack::empty() const noexcept {
  return buf_.empty();
}