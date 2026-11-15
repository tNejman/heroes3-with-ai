#pragma once

#include <memory>
#include <set>
#include <utility>

#include <SFML/Window/Keyboard.hpp>

#include "core/Game/IKeyHandler.h"
#include "core/Game/KeyHandler.h"

template <typename MoveType>
class KeyHandlerUnbuffered : public IKeyboardHandler<MoveType> {
 private:
  std::unique_ptr<IKeyboardInput> input_;
  std::map [[nodiscard]] KeyHandlerUnbuffered( std::unique_ptr<IKeyboardInput> input ) noexcept
      : input_( std::move( input ) ) {
  }

 public:
  [[nodiscard]] MoveType monitorKeyPressesAndGetMove() noexcept {
    std::set<sf::Keyboard::Key> currently_pressed = input_->pressedNow();
  }
};