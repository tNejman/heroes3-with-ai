#include <engine/Graphics/GraphicsLib.h>
#include <engine/Graphics/Renderers/GameRenderer.h>
#include <engine/Input/InputHandler.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "core/Character/Character.h"
#include "core/Character/CharacterBuilder.h"
#include "core/Character/CharacterStats.h"
#include "core/Game/Game.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/Coords.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"

constexpr inline int FRAMES_PER_SECOND = 30;

constexpr inline std::string WINDOW_NAME = "Heroes3App";

int main() {
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

  characters[0]->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 10 } );
  characters[0]->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 15 } );
  characters[0]->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 10 } );

  std::vector<std::shared_ptr<Character>> characters_2;
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 2, 2 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .setIsUser( false )
          .buildSharedPtr() );
  characters_2.push_back(
      CharacterBuilder{}
          .setName( "black_hero_white_horse_down_right" )
          .setCoords( { 12, 12 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 12, .defense_ = 15, .power_ = 8, .knowledge_ = 2 },
              CharacterStats::Misc{ .morale_ = 5, .luck_ = -2 } } )
          .setIsUser( false )
          .buildSharedPtr() );

  characters_2[0]->army().recruitUnitStack( UnitStack{ CastleUnitType::SWORDSMAN, 5 } );
  characters_2[0]->army().recruitUnitStack( UnitStack{ CastleUnitType::ARCHER, 10 } );

  characters_2[1]->army().recruitUnitStack( UnitStack{ CastleUnitType::MONK, 5 } );
  characters_2[1]->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 5 } );

  std::vector<std::shared_ptr<Player>> players;
  players.push_back( std::make_shared<Player>( std::move( characters ) ) );
  players.push_back( std::make_shared<Player>( std::move( characters_2 ) ) );

  Game game{ std::move( players ) };

  // std::ofstream out( "CharacterSave2.txt" );
  // CharacterSaver character_saver = CharacterSaver( "CharacterSave2.txt", characters[0] );
  // character_saver.save();
  // CharacterSaver character_saver2 = CharacterSaver( "CharacterSave2.txt", characters_2[0] );
  // character_saver2.save();
  // CharacterSaver character_saver3 = CharacterSaver( "CharacterSave2.txt", characters_2[1] );
  // character_saver3.save();

  // TODO make NOT shared_ptr
  std::shared_ptr<sf::RenderWindow> window =
      std::make_shared<sf::RenderWindow>( sf::VideoMode( { graphics::WINDOW_WIDTH, graphics::WINDOW_HEIGHT } ),
                                          WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close );
  window->setFramerateLimit( FRAMES_PER_SECOND );
  window->setSize( sf::Vector2u( graphics::WINDOW_WIDTH, graphics::WINDOW_HEIGHT ) );
  GameRenderer{ *window, game }.render();
  while ( window->isOpen() ) {
    if ( window->getSize() != sf::Vector2u( graphics::WINDOW_WIDTH, graphics::WINDOW_HEIGHT ) ) {
      window->setSize( { graphics::WINDOW_WIDTH, graphics::WINDOW_HEIGHT } );
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
      } else {
        command = InputHandler::processInput( *event, game );  // only the last command of a game iteration is recorded
      }
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