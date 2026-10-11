#include "engine/Input/InputHandler.h"

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <chrono>

#include "core/Game/Game.h"
#include "core/Game/UserCommand.hpp"
#include "core/Misc/ProjectLib.h"
#include "engine/IGame/Coords.h"
#include "engine/Input/KeyboardHandler.h"
#include "engine/Input/MouseHandler.h"

CoordPair InputHandler::calculateNewCharacterPosition( CoordPair old_coords,
                                                       CharacterMoveDirection direction ) noexcept {
  return old_coords + WORLD_MAP_DIRECTIONS[static_cast<size_t>( direction )];
}

[[nodiscard]] game::UserCommandInputHandler::processMouseInput( const sf::Event& event, const Game& game ) noexcept {
  if ( event.getIf<sf::Event::MouseButtonPressed>()->button != sf::Mouse::Button::Left ) {
    return None{};
  }
  MouseHandler mouse_handler{};
  mouse_handler.updateMouseCoords( MouseCoords{ .x = event.getIf<sf::Event::MouseButtonPressed>()->position.x,
                                                .y = event.getIf<sf::Event::MouseButtonPressed>()->position.y } );
  game.getState().accept( mouse_handler );
  return mouse_handler.getCommand();
}

[[nodiscard]] game::UserCommandInputHandler::processKeyboardInput( const sf::Event&, const Game& game ) noexcept {
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

game::UserCommandInputHandler::processInput( const sf::Event& event, const Game& game ) noexcept {
  if ( event.is<sf::Event::MouseButtonPressed>() ) {
    return processMouseInput( event, game );
  }
  return processKeyboardInput( event, game );
}