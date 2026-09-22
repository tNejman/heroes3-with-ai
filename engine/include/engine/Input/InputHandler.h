#pragma once

#include <SFML/Window/Event.hpp>

#include "core/Game/Game.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"

class InputHandler {
 private:
  static inline bool was_input_just_processed = false;

  static CoordPair calculateNewCharacterPosition( CoordPair old_coords, CharacterMoveDirection direction ) noexcept;

  [[nodiscard]] static UserCommand processMouseInput( const sf::Event&, const Game&, int window_scale ) noexcept;
  [[nodiscard]] static UserCommand processKeyboardInput( const sf::Event&, const Game& ) noexcept;

 public:
  [[nodiscard]] static UserCommand processInput( const sf::Event&, const Game&, int window_scale ) noexcept;
};