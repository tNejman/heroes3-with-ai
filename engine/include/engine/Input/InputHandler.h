#pragma once

#include <SFML/Window/Event.hpp>

#include "core/Game/Game.h"
#include "core/Game/UserCommand.hpp"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"

class InputHandler {
 private:
  static inline bool was_input_just_processed = false;

  static CoordPair calculateNewCharacterPosition( CoordPair old_coords, CharacterMoveDirection direction ) noexcept;

  [[nodiscard]] static game::UserCommandprocessMouseInput( const sf::Event&, const Game& ) noexcept;
  [[nodiscard]] static game::UserCommandprocessKeyboardInput( const sf::Event&, const Game& ) noexcept;

 public:
  [[nodiscard]] static game::UserCommandprocessInput( const sf::Event&, const Game& ) noexcept;
};