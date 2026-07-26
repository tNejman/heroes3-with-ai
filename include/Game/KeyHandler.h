#pragma once

#include <SFML/Window.hpp>
#include <algorithm>
#include <deque>
#include <map>
#include <memory>
#include <set>

#include "Characters/Character.h"
#include "Exceptions/UnknownStateException.hpp"
#include "Exceptions/_NotImplementedException.hpp"

// Movement OverworldOnly
class KeyHandler {
 private:
  bool is_buffered_input_ = false;
  // Game extracts one move per frame
  std::vector<ShiftPair> pending_moves_;
  std::deque<std::vector<sf::Keyboard::Key>> key_press_history_;
  std::set<sf::Keyboard::Key> held_keys_;

  void processBufferedInput();
  ShiftPair getShiftFromVector( const std::vector<sf::Keyboard::Key>& key_vec );
  bool isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const;
  bool isDoublePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  bool isSinglePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  // void convertKeyPressesToMoves();

 public:
  KeyHandler();
  KeyHandler(bool is_buffered_input);

  // monitoring is split with getMove because there may be more than 1 move queued
  void monitorKeyPresses();
  ShiftPair getMove();
};