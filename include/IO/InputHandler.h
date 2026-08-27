#pragma once

#include <SFML/Window/Event.hpp>

#include "Game/Game.h"
#include "Game/UserCommand.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

class InputHandler {
 private:
  static inline bool was_input_just_processed = false;

  static CoordPair calculateNewCharacterPosition( CoordPair old_coords, CharacterMoveDirection direction ) noexcept;

  [[nodiscard]] static UserCommand processMouseInput( const sf::Event&, const Game& ) noexcept;
  [[nodiscard]] static UserCommand processKeyboardInput( const sf::Event&, const Game& ) noexcept;

 public:
  [[nodiscard]] static UserCommand processInput( const sf::Event&, const Game& ) noexcept;
};