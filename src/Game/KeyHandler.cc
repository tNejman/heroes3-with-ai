#include "Game/KeyHandler.h"

#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Exceptions/Err.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

void KeyHandler::processBufferedInput() {
  while ( !key_press_history_.empty() ) {
    auto &current = key_press_history_.front();

    if ( isDoublePress( current ) ) {
      pending_moves_.push_back( getMoveFromKeys( current ) );
      key_press_history_.pop_front();
      continue;
    }
    if ( isSinglePress( current ) ) {
      // searching for a match to combine to a double-press
      sf::Keyboard::Key base = current[0];
      bool matched = false;
      bool force_solo = false;
      bool should_wait = false;
      bool incompatible_pair = false;

      int avail = key_press_history_.empty() ? 0 : static_cast<int>( key_press_history_.size() - 1 );
      int max_i = is_buffered_input_ ? std::min( KEY_BUFFER_DURATION, avail ) : std::min( 1, avail );

      for ( size_t i = 1; i <= static_cast<size_t>( max_i ); ++i ) {
        auto &next = key_press_history_[i];

        if ( isDoublePress( next ) ) {
          // single press followed by double; force execute and skip waiting
          force_solo = true;
          break;
        }

        if ( isSinglePress( next ) ) {
          if ( isValidDiagonalPair( base, next[0] ) ) {
            current.push_back( next[0] );
            key_press_history_[i].clear();
            pending_moves_.push_back( getMoveFromKeys( current ) );
            key_press_history_.pop_front();
            matched = true;
            break;
          } else {
            incompatible_pair = true;
            break;
          }
        }
      }

      if ( !matched ) {
        if ( force_solo || incompatible_pair ) {
          // execute instantly
          pending_moves_.push_back( getMoveFromKeys( current ) );
          key_press_history_.pop_front();
        } else if ( is_buffered_input_ ) {
          if ( max_i < KEY_BUFFER_DURATION ) {
            // not enough frames to execute single move
            break;
          }
        } else if ( !should_wait ) {
          // all frames in buffer duration are empty
          pending_moves_.push_back( getMoveFromKeys( current ) );
          key_press_history_.pop_front();
        } else {
          break;
        }
      }

      continue;
    }
    // no keys pressed this frame
    key_press_history_.pop_front();
  }
}

CharacterMoveDirection KeyHandler::getMoveFromKeys( const std::vector<sf::Keyboard::Key> &key_vec ) {
  int dx = 0;
  int dy = 0;
  for ( const auto &key : key_vec ) {
    switch ( key ) {
      case W: dy += 1; break;
      case S: dy -= 1; break;
      case A: dx -= 1; break;
      case D: dx += 1; break;
      default:
        err::raise<std::runtime_error>( "KeyHandler::getMoveFromKeys -> Unexpected key passed to movement control" );
    };
  }

  ShiftPair shift{ dx, dy };

  const auto *itr = std::ranges::find( WORLD_MAP_DIRECTIONS.begin(), WORLD_MAP_DIRECTIONS.end(), shift );

  if ( itr == WORLD_MAP_DIRECTIONS.end() ) {
    return CharacterMoveDirection::NONE;
  }
  auto dist = std::distance( WORLD_MAP_DIRECTIONS.begin(), itr );
  assert( dist <= 7U );
  return static_cast<CharacterMoveDirection>( dist );
}

bool KeyHandler::isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const {
  auto it = VALID_DIAGONAL_MOVE_COMP.find( first );
  if ( it == VALID_DIAGONAL_MOVE_COMP.end() ) return false;

  return second == it->second[0] || second == it->second[1];
}

bool KeyHandler::isDoublePress( const std::vector<sf::Keyboard::Key> &keys ) const {
  return keys.size() == 2;
}

bool KeyHandler::isSinglePress( const std::vector<sf::Keyboard::Key> &keys ) const {
  return keys.size() == 1;
}

KeyHandler::KeyHandler( bool is_buffered_input )
    : is_buffered_input_( is_buffered_input ), input_( std::make_shared<RealKeyboardInput>() ) {};

KeyHandler::KeyHandler( bool is_buffered_input, bool is_mock_input ) : is_buffered_input_( is_buffered_input ) {
  if ( is_mock_input ) {
    input_ = std::make_shared<MockKeyboardInput>();
  } else {
    input_ = std::make_shared<RealKeyboardInput>();
  }
}

void KeyHandler::debugMockInput( std::shared_ptr<IKeyboardInput> input ) {
  input_ = std::move( input );
}

void KeyHandler::monitorKeyPresses() {
  std::vector<sf::Keyboard::Key> keys_this_frame;
  std::set<sf::Keyboard::Key> currently_pressed = input_->pressedNow();

  for ( const auto &key : MOVEMENT_KEYS ) {
    //   if ( sf::Keyboard::isKeyPressed( key ) ) {
    //     currently_pressed.insert( key );
    //     if ( !held_keys_.contains( key ) && keys_this_frame.size() < 2 ) {
    //       keys_this_frame.push_back( key );
    //     }
    //   }
    if ( currently_pressed.contains( key ) && !held_keys_.contains( key ) && keys_this_frame.size() < 2 ) {
      keys_this_frame.push_back( key );
    }
  }
  held_keys_ = currently_pressed;
  key_press_history_.push_back( keys_this_frame );
}

CharacterMoveDirection KeyHandler::getMove() {
  // convertKeyPressesToMoves();
  processBufferedInput();

  if ( pending_moves_.empty() ) {
    return CharacterMoveDirection::NONE;
  }
  auto ret_move = pending_moves_.front();
  pending_moves_.erase( pending_moves_.begin() );
  // std::cout << "DEBUG: KeyHandler returns move: dx=" << ret_move.dx_ << " dy=" << ret_move.dy_ << std::endl;
  return ret_move;
}