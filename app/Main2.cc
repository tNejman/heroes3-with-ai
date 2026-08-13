#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <utility>

#include "Graphics/SpriteFactory.h"
#include "Miscellaneous/ProjectLib.h"

int main() {
  std::string file_path = "sprites/heroes_adventure.png";
  sf::Texture texture;
  if ( !texture.loadFromFile( file_path ) ) {
    return -1;
  }
  sf::Sprite sprite( texture, sf::IntRect{ { 0, 0 }, { 95, 64 } } );

  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
      sf::VideoMode( { 200, 200 } ), "heroes", sf::Style::Titlebar | sf::Style::Close );
  window->setFramerateLimit( 30 );

  CharacterType ct = CharacterType::FIRE_HERO;
  CharacterMoveDirection cmd = CharacterMoveDirection::UP_LEFT;
  while ( true ) {
    cmd = static_cast<CharacterMoveDirection>( ( std::to_underlying( cmd ) + 1 )
                                               % ( std::to_underlying( CharacterMoveDirection::NONE ) ) );
    std::this_thread::sleep_for( std::chrono::milliseconds{ 250 } );
    window->clear( sf::Color( 4 ) );
    window->draw( SpriteFactory::getSpriteFromBinding( ct, cmd ) );
    window->display();
  }
}