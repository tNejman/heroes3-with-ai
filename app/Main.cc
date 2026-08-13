#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
#include <utility>
#include <vector>

#include "Character/Character.h"
#include "Character/CharacterBuilder.h"
#include "Character/CharacterStats.h"
#include "Game/Game.h"
// #include "LoadAndSaveTools/CharacterSaver.h"
#include "Game/KeyboardHandler.h"
#include "Game/MouseHandler.h"
#include "Game/UserCommand.h"
#include "Graphics/Renderers/GameRenderer.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "Unit/UnitStack.h"
#include "Unit/UnitsLib.h"
#include "WorldMap/OverworldObstacle.h"

namespace {
ShiftPair getShiftFromDirection( CharacterMoveDirection direction ) {
  return WORLD_MAP_DIRECTIONS[static_cast<size_t>( direction )];
}

}  // namespace

int main() {
  UnitStack unit_stack_1{ getCastleUnit( CastleUnitType::PIKEMAN ), 10 };
  UnitStack unit_stack_3{ getCastleUnit( CastleUnitType::PIKEMAN ), 15 };
  UnitStack unit_stack_4{ getCastleUnit( CastleUnitType::ANGEL ), 10 };

  UnitStack unit_stack_2{ getCastleUnit( CastleUnitType::SWORDSMAN ), 5 };
  UnitStack unit_stack_5{ getCastleUnit( CastleUnitType::ARCHER ), 10 };

  UnitStack unit_stack_6{ getCastleUnit( CastleUnitType::MONK ), 5 };
  UnitStack unit_stack_7{ getCastleUnit( CastleUnitType::PIKEMAN ), 5 };

  std::vector<std::shared_ptr<Character>> characters;
  characters.push_back(
      CharacterBuilder{}
          .setName( "fire_hero_down_right" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr() );

  characters[0]->army().recruitUnitStack( unit_stack_1 );
  characters[0]->army().recruitUnitStack( unit_stack_3 );
  characters[0]->army().recruitUnitStack( unit_stack_4 );

  std::vector<std::shared_ptr<Character>> characters_2;
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr() );
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 12, .defense_ = 15, .power_ = 8, .knowledge_ = 2 },
              CharacterStats::Misc{ .morale_ = 5, .luck_ = -2 } } )
          .buildSharedPtr() );

  characters_2[0]->setIfUser( false );
  characters_2[0]->army().recruitUnitStack( unit_stack_2 );
  characters_2[0]->army().recruitUnitStack( unit_stack_5 );
  characters_2[0]->setCoords( CoordPair( 10u, 10u ) );

  characters_2[1]->setIfUser( false );
  characters_2[1]->army().recruitUnitStack( unit_stack_6 );
  characters_2[1]->army().recruitUnitStack( unit_stack_7 );
  characters_2[1]->setCoords( CoordPair( 12u, 12u ) );

  std::vector<std::shared_ptr<Player>> players;
  players.push_back( std::make_shared<Player>( std::move( characters ) ) );
  players.push_back( std::make_shared<Player>( std::move( characters_2 ) ) );

  std::shared_ptr<Game> game = std::make_shared<Game>( players );

  // std::ofstream out( "CharacterSave2.txt" );
  // CharacterSaver character_saver = CharacterSaver( "CharacterSave2.txt", characters[0] );
  // character_saver.save();
  // CharacterSaver character_saver2 = CharacterSaver( "CharacterSave2.txt", characters_2[0] );
  // character_saver2.save();
  // CharacterSaver character_saver3 = CharacterSaver( "CharacterSave2.txt", characters_2[1] );
  // character_saver3.save();

  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode( { WINDOW_WIDTH, WINDOW_HEIGHT } ), WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close );
  window->setFramerateLimit( 30 );
  window->setSize( sf::Vector2u( WINDOW_WIDTH, WINDOW_HEIGHT ) );
  while ( window->isOpen() ) {
    if ( window->getSize() != sf::Vector2u( WINDOW_WIDTH, WINDOW_HEIGHT ) ) {
      window->setSize( { WINDOW_WIDTH, WINDOW_HEIGHT } );
    }
    // sf::Time start_time = clock.getElapsedTime();

    UserCommand maybe_command = None{};

    while ( std::optional event = window->pollEvent() ) {
      if ( event->is<sf::Event::Closed>() ) {
        window->close();
        return 0;
      }
      std::optional<CoordPair> maybe_hex_coords = [&] -> std::optional<CoordPair> {
        if ( event->is<sf::Event::MouseButtonPressed>()
             && event->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left ) {
          int mouse_x = event->getIf<sf::Event::MouseButtonPressed>()->position.x;
          int mouse_y = event->getIf<sf::Event::MouseButtonPressed>()->position.y;
          return MouseHandler{}.getHexagonCoordsFromClick( mouse_x, mouse_y );
        }
        return std::nullopt;
      }();
      if ( maybe_hex_coords.has_value() ) {
        maybe_command = BattleCommand{ maybe_hex_coords.value() };
      } else {
        KeyHandler key_handler{ false };
        key_handler.monitorKeyPresses();
        CharacterMoveDirection move_direction = key_handler.getMove();
        if ( move_direction != CharacterMoveDirection::NONE ) {
          CoordPair source = game->getMainCharacter()->getCoords();
          CoordPair destination = game->getMainCharacter()->getCoords() + getShiftFromDirection( move_direction );
          maybe_command = MoveCharacter{ .source_ = source, .destination_ = destination };
        }
      }
    }
    window->clear( sf::Color( 4 ) );
    game->applyCommand( maybe_command );
    // std::this_thread::sleep_for( std::chrono::milliseconds{ 500 } );
    GameRenderer{ *game }.render( *window, game->getMainCharacter()->getCoords() );
    // if ( game->getFrameCountSinceStart() == 4 ) {
    //   std::chrono::milliseconds timespan{ 5'000 };
    //   std::this_thread::sleep_for( timespan );
    // }
    window->display();
  }
};