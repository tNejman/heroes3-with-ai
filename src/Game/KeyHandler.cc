#include "Game/KeyHandler.h"

#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstdint>
#include <set>
#include <stdexcept>
#include <vector>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

void KeyHandler::processBufferedInput() {
  while ( !key_press_history_.empty() ) {
    auto &current = key_press_history_.front();

    if ( isDoublePress( current ) ) {
      pending_moves_.push_back( getShiftFromVector( current ) );
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

      FrameCount max_i = is_buffered_input_
                             ? std::min<FrameCount>( KEY_BUFFER_DURATION, uint32_t( key_press_history_.size() ) - 1 )
                             : 1;

      for ( FrameCount i = 1; i <= max_i; ++i ) {
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
            pending_moves_.push_back( getShiftFromVector( current ) );
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
          pending_moves_.push_back( getShiftFromVector( current ) );
          key_press_history_.pop_front();
        } else if ( is_buffered_input_ ) {
          if ( max_i < KEY_BUFFER_DURATION ) {
            // not enough frames to execute single move
            break;
          }
        } else if ( !should_wait ) {
          // all frames in buffer duration are empty
          pending_moves_.push_back( getShiftFromVector( current ) );
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

ShiftPair KeyHandler::getShiftFromVector( const std::vector<sf::Keyboard::Key> &key_vec ) {
  int dx = 0;
  int dy = 0;
  for ( auto &key : key_vec ) {
    switch ( key ) {
      case W: dy += 1; break;
      case S: dy -= 1; break;
      case A: dx -= 1; break;
      case D: dx += 1; break;
      default: throw std::runtime_error( "Unexpected key passed to movement control" );
    };
  }
  return ShiftPair( dx, dy );
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

KeyHandler::KeyHandler() {};

KeyHandler::KeyHandler( bool is_buffered_input ) : is_buffered_input_( is_buffered_input ) {};

void KeyHandler::monitorKeyPresses() {
  std::vector<sf::Keyboard::Key> keys_this_frame;
  std::set<sf::Keyboard::Key> currently_pressed;

  for ( auto &key : MOVEMENT_KEYS ) {
    if ( sf::Keyboard::isKeyPressed( key ) ) {
      currently_pressed.insert( key );
      if ( held_keys_.count( key ) == 0 && keys_this_frame.size() < 2 ) {
        keys_this_frame.push_back( key );
      }
    }
  }
  held_keys_ = currently_pressed;
  key_press_history_.push_back( keys_this_frame );
}

ShiftPair KeyHandler::getMove() {
  // convertKeyPressesToMoves();
  processBufferedInput();

  if ( pending_moves_.empty() ) {
    return ShiftPair( 0, 0 );
  }
  ShiftPair ret_move = pending_moves_.front();
  pending_moves_.erase( pending_moves_.begin() );
  // std::cout << "DEBUG: KeyHandler returns move: dx=" << ret_move.dx_ << " dy=" << ret_move.dy_ << std::endl;
  return ret_move;
}