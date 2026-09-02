#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <memory>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

#include "Character/Character.h"
#include "Character/CharacterBuilder.h"
#include "Character/CharacterStats.h"
#include "Game/Game.h"
#include "Game/UserCommand.h"
#include "Graphics/Renderers/GameRenderer.h"
#include "IO/InputHandler.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "Unit/UnitStack.h"
#include "Unit/UnitsLib.h"

int main() {
  UnitStack unit_stack_1{ CastleUnitType::PIKEMAN, 10 };
  UnitStack unit_stack_3{ CastleUnitType::PIKEMAN, 15 };
  UnitStack unit_stack_4{ CastleUnitType::ANGEL, 10 };

  UnitStack unit_stack_2{ CastleUnitType::SWORDSMAN, 5 };
  UnitStack unit_stack_5{ CastleUnitType::ARCHER, 10 };

  UnitStack unit_stack_6{ CastleUnitType::MONK, 5 };
  UnitStack unit_stack_7{ CastleUnitType::PIKEMAN, 5 };

  std::vector<std::shared_ptr<Character>> characters;
  characters.push_back(
      CharacterBuilder{}
          .setName( "fire_hero_down_right" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr() );
  characters.push_back( CharacterBuilder{}
                            .setName( "john" )
                            .setCoords( { 5, 5 } )
                            .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                           .attack_ = 5, .defense_ = 5, .power_ = 5, .knowledge_ = 5 },
                                                       CharacterStats::Misc{ .morale_ = 1, .luck_ = 1 } } )
                            .buildSharedPtr() );

  characters[0]->army().recruitUnitStack( unit_stack_1 );
  characters[0]->army().recruitUnitStack( unit_stack_3 );
  characters[0]->army().recruitUnitStack( unit_stack_4 );

  std::vector<std::shared_ptr<Character>> characters_2;
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 2, 2 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr() );
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 12, 12 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 12, .defense_ = 15, .power_ = 8, .knowledge_ = 2 },
              CharacterStats::Misc{ .morale_ = 5, .luck_ = -2 } } )
          .buildSharedPtr() );

  characters_2[0]->setIfUser( false );
  characters_2[0]->army().recruitUnitStack( unit_stack_2 );
  characters_2[0]->army().recruitUnitStack( unit_stack_5 );

  characters_2[1]->setIfUser( false );
  characters_2[1]->army().recruitUnitStack( unit_stack_6 );
  characters_2[1]->army().recruitUnitStack( unit_stack_7 );

  std::vector<std::shared_ptr<Player>> players;
  players.push_back( std::make_shared<Player>( std::move( characters ) ) );
  players.push_back( std::make_shared<Player>( std::move( characters_2 ) ) );

  Game game{ players };

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
  GameRenderer{ *window, game }.render();
  while ( window->isOpen() ) {
    if ( window->getSize() != sf::Vector2u( WINDOW_WIDTH, WINDOW_HEIGHT ) ) {
      window->setSize( { WINDOW_WIDTH, WINDOW_HEIGHT } );
    }
    // sf::Time start_time = clock.getElapsedTime();

    UserCommand command = None{};

    while ( std::optional event = window->pollEvent() ) {
      if ( event->is<sf::Event::Closed>() ) {
        window->close();
        return 0;
      }
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Q ) ) {
        command = SwitchCharacter{};
      } else
        command = InputHandler::processInput( *event, game );  // only the last command of a game iteration is recorded
    }
    game.applyCommand( command );
    GameRenderer{ *window, game }.render();
    // std::this_thread::sleep_for( std::chrono::milliseconds{ 500 } );
    if ( !std::holds_alternative<None>( command ) ) {
      // const auto& state = game->getState();
      // std::cout << typeid( state ).name() << '\n';
    }
    // if ( game->getFrameCountSinceStart() == 4 ) {
    //   std::chrono::milliseconds timespan{ 5'000 };
    //   std::this_thread::sleep_for( timespan );
    // }
  }
};