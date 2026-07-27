#pragma once

#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <deque>
#include <set>
#include <vector>

#include "Miscellaneous/ProjectLib.h"

// Movement OverworldOnly
class KeyHandler {
 private:
  bool is_buffered_input_ = false;
  // Game extracts one move per frame
  std::vector<CharacterMoveDirection> pending_moves_;
  std::deque<std::vector<sf::Keyboard::Key>> key_press_history_;
  std::set<sf::Keyboard::Key> held_keys_;

  void processBufferedInput();
  CharacterMoveDirection getMoveFromKeys( const std::vector<sf::Keyboard::Key>& key_vec );
  [[nodiscard]] bool isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const;
  [[nodiscard]] bool isDoublePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  [[nodiscard]] bool isSinglePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  // void convertKeyPressesToMoves();

 public:
  KeyHandler();
  KeyHandler( bool is_buffered_input );

  // monitoring is split with getMove because there may be more than 1 move queued
  void monitorKeyPresses();
  CharacterMoveDirection getMove();
};