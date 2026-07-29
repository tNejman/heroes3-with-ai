#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <set>
#include <utility>

#include "Game/IKeyHandler.h"
#include "Game/KeyHandler.h"

template <typename MoveType>
class KeyHandlerUnbuffered : public IKeyboardHandler<MoveType> {
 private:
  std::unique_ptr<IKeyboardInput> input_;
  std::map
  KeyHandlerUnbuffered( std::unique_ptr<IKeyboardInput> input ) : input_( std::move( input ) ) {
  }

 public:
  MoveType monitorKeyPressesAndGetMove() {
    std::set<sf::Keyboard::Key> currently_pressed = input_->pressedNow();
  }
};