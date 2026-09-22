#include <engine/Graphics/GraphicsLib.h>
#include <engine/Graphics/Renderers/GameRenderer.h>
#include <engine/Input/InputHandler.h>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <array>
#include <memory>
#include <utility>
#include <vector>

#include "aux/Err.hpp"
#include "core/Character/Character.h"
#include "core/Character/CharacterBuilder.h"
#include "core/Character/CharacterStats.h"
#include "core/Game/Game.h"
#include "core/Game/UserCommand.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"
#include "engine/IGame/Coords.h"


constexpr inline int FRAMES_PER_SECOND = 30;

constexpr inline std::string WINDOW_NAME = "Heroes3App";

namespace {

int window_scale_mult = 3;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

void preMain() {
}

}  // namespace

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

int main() {
  preMain();

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

  sf::RenderWindow window{
      sf::VideoMode{ sf::Vector2u{ static_cast<unsigned int>( graphics::WINDOW_WIDTH * window_scale_mult ),
                                   static_cast<unsigned int>( graphics::WINDOW_HEIGHT * window_scale_mult ) } },
      WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close };
  window.setFramerateLimit( FRAMES_PER_SECOND );
  window.setPosition( sf::Vector2i{ 0, 0 } );

  sf::RenderTexture target;
  err::passCondOrAbort( target.resize( sf::Vector2u{ static_cast<unsigned int>( graphics::WINDOW_WIDTH ),
                                                     static_cast<unsigned int>( graphics::WINDOW_HEIGHT ) } ) );
  target.setSmooth( false );

  while ( window.isOpen() ) {
    if ( window.getSize()
         != sf::Vector2u( static_cast<unsigned int>( graphics::WINDOW_WIDTH * window_scale_mult ),
                          static_cast<unsigned int>( graphics::WINDOW_HEIGHT * window_scale_mult ) ) ) {
      window.setSize( { static_cast<unsigned int>( graphics::WINDOW_WIDTH * window_scale_mult ),
                        static_cast<unsigned int>( graphics::WINDOW_HEIGHT * window_scale_mult ) } );
      window.setView( sf::View{ sf::FloatRect{ { 0.F, 0.F }, sf::Vector2f{ window.getSize() } } } );
    }

    UserCommand command = None{};

    while ( std::optional event = window.pollEvent() ) {
      if ( event->is<sf::Event::Closed>() ) {
        window.close();
        return 0;
      }
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Q ) ) {
        command = SwitchCharacter{};
      } else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num1 ) ) {
        window_scale_mult = 1;
      } else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num2 ) ) {
        window_scale_mult = 2;
      } else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Num3 ) ) {
        window_scale_mult = 3;
      } else {
        command = InputHandler::processInput( *event, game, window_scale_mult );
      }
    }
    game.applyCommand( command );
    GameRenderer{ window, target, game }.render();
  }
};

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)