#pragma once

#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <deque>
#include <memory>
#include <set>
#include <vector>

#include "IO/IKeyboardInput.hpp"
#include "Miscellaneous/ProjectLib.h"

// Movement OverworldOnly
class KeyHandler {
 private:
  bool is_buffered_input_ = false;
  std::vector<CharacterMoveDirection> pending_moves_;  // Game extracts one move per frame
  std::deque<std::vector<sf::Keyboard::Key>> key_press_history_;
  std::set<sf::Keyboard::Key> held_keys_;
  std::shared_ptr<IKeyboardInput> input_;

  void processBufferedInput();
  CharacterMoveDirection getMoveFromKeys( const std::vector<sf::Keyboard::Key>& key_vec );
  [[nodiscard]] bool isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const;
  [[nodiscard]] bool isDoublePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  [[nodiscard]] bool isSinglePress( const std::vector<sf::Keyboard::Key>& keys ) const;
  // void convertKeyPressesToMoves();
  void removeEmptyFramesFromFront();
  [[nodiscard]] int getFrameCountLookup() const noexcept;

 public:
  KeyHandler() = delete;
  KeyHandler( bool is_buffered_input );
  KeyHandler( bool is_buffered, bool is_mock_input );

  // monitoring is split with getMove because there may be more than 1 move queued
  void debugMockInput( std::shared_ptr<IKeyboardInput> mock_input );
  void monitorKeyPresses();
  CharacterMoveDirection getMove();
};