#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <chrono>
#include <iostream>
#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <string>
#include <thread>

#include "Artifact/ArtifactLib.h"
#include "Graphics/SpriteFactory.h"
#include "Miscellaneous/CycleEnumVal.hpp"

// int main( int, char* argv[] ) {
int main() {
  std::cout << sizeof( int ) << std::endl;

  // std::string file_path = "sprites/heroes_adventure.png";
  // sf::Texture texture;
  // if ( !texture.loadFromFile( file_path ) ) {
  //   return -1;
  // }
  // sf::Sprite sprite( texture, sf::IntRect{ { 0, 0 }, { 95, 64 } } );

  // std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(
  //     sf::VideoMode( { 1000, 1000 } ), "heroes", sf::Style::Titlebar | sf::Style::Close );
  // window->setFramerateLimit( 30 );

  // // bool sprite_base = true;
  // // bool sprite_base_vert = true;

  // // int horizontal_crop = 62;
  // // int vertical_crop = 113;

  // // sf::Texture tex;
  // // err::passCondOrAbort( tex.loadFromFile( "sprites/units/castle/" + std::string{ argv[1] } + ".png" ) );
  // // err::passCondOrAbort( tex.loadFromFile( "sprites/artifacts/artifacts.png" ) );

  // auto a = static_cast<ArtifactType>( 0 );

  // // int vert_cut = 0;
  // while ( true ) {
  //   while ( auto maybe_event = window->pollEvent() ) {
  //     if ( maybe_event->is<sf::Event::KeyPressed>() ) {
  //       switch ( maybe_event->getIf<sf::Event::KeyPressed>()->code ) {
  //         case sf::Keyboard::Key::Left: {
  //           a = prev( a );
  //           break;
  //         }
  //         case sf::Keyboard::Key::Right: {
  //           a = next( a );
  //           break;
  //         }
  //         // case sf::Keyboard::Key::Up: --vert_cut; break;
  //         // case sf::Keyboard::Key::Down: ++vert_cut; break;
  //         // case sf::Keyboard::Key::D: sprite_base = false; break;
  //         // case sf::Keyboard::Key::A: sprite_base = true; break;
  //         // case sf::Keyboard::Key::W: sprite_base_vert = true; break;
  //         // case sf::Keyboard::Key::S: sprite_base_vert = false; break;
  //         // case sf::Keyboard::Key::C: std::cin >> vert_cut; break;
  //         default:
  //       }
  //       std::cout << magic_enum::enum_name( a ) << std::endl;
  //       // std::println( "horizontal_crop={}, vertical_crop={}, base_sprite?={}", horizontal_crop, vertical_crop,
  //       //               sprite_base );
  //       std::this_thread::sleep_for( std::chrono::milliseconds{ 100 } );
  //     }
  //   }

  //   // std::this_thread::sleep_for( std::chrono::milliseconds{ 250 } );
  //   window->clear( sf::Color( 4 ) );
  //   // int hor_pos = ( sprite_base ) ? 0 : horizontal_crop;
  //   // int ver_pos = ( sprite_base_vert ) ? 0 : vertical_crop;
  //   // window->draw( sf::Sprite{ tex, sf::IntRect{ { hor_pos, ver_pos }, { horizontal_crop, vert_cut } } } );
  //   window->draw( SpriteFactory::getSpriteFromBindingV( a ) );
  //   window->display();
  // }
}