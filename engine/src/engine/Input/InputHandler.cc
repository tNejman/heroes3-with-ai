#include "engine/Input/InputHandler.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "core/Game/Game.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"
#include "engine/Input/KeyboardHandler.h"
#include "engine/Input/MouseHandler.h"

/* ===== @PRIVATE ===== */

CoordPair InputHandler::calculateNewCharacterPosition( CoordPair old_coords,
                                                       CharacterMoveDirection direction ) noexcept {
  return old_coords + WORLD_MAP_DIRECTIONS[static_cast<size_t>( direction )];
}

[[nodiscard]] UserCommand InputHandler::processMouseInput( const sf::Event& event, const Game& game,
                                                           int window_scale ) noexcept {
  const auto* pressed = event.getIf<sf::Event::MouseButtonPressed>();
  if ( pressed->button != sf::Mouse::Button::Left ) {
    return None{};
  }
  MouseHandler mouse_handler{};
  mouse_handler.updateMouseCoords(
      MouseCoords{ .x = pressed->position.x / window_scale, .y = pressed->position.y / window_scale } );
  game.getState().accept( mouse_handler );
  return mouse_handler.getCommand();
}

[[nodiscard]] UserCommand InputHandler::processKeyboardInput( const sf::Event&, const Game& game ) noexcept {
  KeyHandler key_handler{ false };
  key_handler.monitorKeyPresses();
  CharacterMoveDirection move_direction = key_handler.getMove();
  if ( move_direction == CharacterMoveDirection::NONE ) {
    return None{};
  }
  CoordPair source = game.getContext().getCurrentCharacter().getCoords();
  CoordPair destination = calculateNewCharacterPosition( source, move_direction );
  return MoveCharacter{ .source_ = source, .destination_ = destination };
}

/* ===== @PUBLIC ===== */

UserCommand InputHandler::processInput( const sf::Event& event, const Game& game, int window_scale ) noexcept {
  if ( event.is<sf::Event::MouseButtonPressed>() ) {
    return processMouseInput( event, game, window_scale );
  }
  return processKeyboardInput( event, game );
}