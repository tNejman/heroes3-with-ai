#pragma once

#include <deque>
#include <memory>
#include <optional>
#include <set>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "engine/platform/Input/IKeyboardInput.hpp"

#include "core/Misc/ProjectLib.h"


// Movement OverworldOnly
class KeyHandler {
 private:
  bool is_buffered_input_ = false;
  std::vector<std::optional<CharacterMoveDirection>> pending_moves_;  // Game extracts one move per frame
  std::deque<std::vector<sf::Keyboard::Key>> key_press_history_;
  std::set<sf::Keyboard::Key> held_keys_;
  std::shared_ptr<IKeyboardInput> input_;

  void processBufferedInput();
  [[nodiscard]] std::optional<CharacterMoveDirection> getMoveFromKeys(
      const std::vector<sf::Keyboard::Key>& key_vec ) noexcept;
  [[nodiscard]] bool isValidDiagonalPair( sf::Keyboard::Key first, sf::Keyboard::Key second ) const noexcept;
  [[nodiscard]] bool isDoublePress( const std::vector<sf::Keyboard::Key>& keys ) const noexcept;
  [[nodiscard]] bool isSinglePress( const std::vector<sf::Keyboard::Key>& keys ) const noexcept;
  // void convertKeyPressesToMoves();
  void removeEmptyFramesFromFront() noexcept;
  [[nodiscard]] int getFrameCountLookup() const noexcept;

 public:
  KeyHandler() = delete;
  [[nodiscard]] KeyHandler( bool is_buffered_input ) noexcept;
  [[nodiscard]] KeyHandler( bool is_buffered, bool is_mock_input ) noexcept;

  // monitoring is split with getMove because there may be more than 1 move queued
  void debugMockInput( std::shared_ptr<IKeyboardInput> mock_input ) noexcept;
  void monitorKeyPresses() noexcept;
  [[nodiscard]] std::optional<CharacterMoveDirection> getMove() noexcept;
};