
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <memory>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "IO/KeyboardHandler.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

// void KeyHandler::processBufferedInput() {
//   removeEmptyFramesFromFront();
//   if ( key_press_history_.empty() ) {
//     return;
//   }
//   auto &current_frame_keys = key_press_history_.front();

//   if ( isDoublePress( current_frame_keys ) ) {
//     // double press is not buffered or ambiguous => transform instantly
//     pending_moves_.push_back( getMoveFromKeys( current_frame_keys ) );
//     key_press_history_.pop_front();
//     return;
//   }
//   if ( isSinglePress( current_frame_keys ) ) {
//     // searching for a match to combine to a double-press
//     sf::Keyboard::Key key_to_be_matched = current_frame_keys[0];
//     int matched_idx = -1;
//     bool force_solo = false;
//     bool incompatible_pair = false;

//     int max_frames_forward = getFrameCountLookup();

//     for ( int i = 1; i <= max_frames_forward; ++i ) {
//       auto &ith_frame_keys = key_press_history_[static_cast<size_t>( i )];

//       if ( isDoublePress( ith_frame_keys ) ) {
//         // single press (current) followed by double (ith); force execute and skip waiting
//         force_solo = true;
//         break;
//       }
//       if ( isSinglePress( ith_frame_keys ) && isValidDiagonalPair( key_to_be_matched, ith_frame_keys[0] ) ) {
//         matched_idx = i;
//         break;
//       }
//       if ( isSinglePress( ith_frame_keys ) && !isValidDiagonalPair( key_to_be_matched, ith_frame_keys[0] ) ) {
//         incompatible_pair = true;
//         break;
//       }
//       // empty frame
//     }
//     if ( matched_idx != -1 ) {
//       std::vector<sf::Keyboard::Key> matched_key_pair{ current_frame_keys[0],
//                                                        key_press_history_[static_cast<size_t>( matched_idx )][0] };

//       current_frame_keys.clear();  // key_press_history_[0]
//       key_press_history_[static_cast<size_t>( matched_idx )].clear();

//       pending_moves_.push_back( getMoveFromKeys( matched_key_pair ) );
//       // key_press_history_.pop_front();

//     } else if ( force_solo || incompatible_pair
//                 || ( is_buffered_input_ && max_frames_forward == KEY_BUFFER_DURATION ) ) {
//       // 1) force_solo means next press was a double and no pair can be created
//       // 2) incompatible_pair means a next key was an incompatible key and no pair can be created
//       // 3) ( is_buffered_input_ && max_frames_forward == KEY_BUFFER_DURATION ) all next frames were empty and buffer
//       is
//       // sufficiently big all three cases mean that we can execute a single move
//       pending_moves_.push_back( getMoveFromKeys( current_frame_keys ) );
//       key_press_history_.pop_front();

//     } else if ( is_buffered_input_ && max_frames_forward < KEY_BUFFER_DURATION ) {
//       // // not enough frames to execute single move
//       // not matched, not forced solo and not incompatible
//       return;
//     } else {
//       err::raise<UnknownStateException>(
//           "SinglePress registered (and buffer sufficiently big) but no matching or "
//           "overriding operation performed " );
//     }
//   }
// }

void KeyHandler::processBufferedInput() {
  removeEmptyFramesFromFront();

  if ( key_press_history_.empty() ) {
    return;
  }

  auto &current_frame_keys = key_press_history_.front();

  if ( isDoublePress( current_frame_keys ) || isSinglePress( current_frame_keys ) ) {
    pending_moves_.push_back( getMoveFromKeys( current_frame_keys ) );
  }

  key_press_history_.pop_front();
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

void KeyHandler::removeEmptyFramesFromFront() {
  while ( key_press_history_.size() > 0 && key_press_history_.front().size() == 0 ) {
    key_press_history_.pop_front();
  }
}

int KeyHandler::getFrameCountLookup() const noexcept {
  if ( !is_buffered_input_ ) {
    return 0;
  }
  int available_length = static_cast<int>( key_press_history_.size() - 2 );
  return std::min( KEY_BUFFER_DURATION, available_length );
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