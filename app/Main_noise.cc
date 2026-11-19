#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <optional>
#include <string>

#include "FastNoiseLite.h"
#include "aux/Err.hpp"
#include "core/WorldMap/WorldMap.h"
#include "engine/platform/Graphics/GraphicsLib.h"
#include "engine/platform/Graphics/Renderers/MapRenderer.h"

constexpr inline int FRAMES_PER_SECOND = 30;

constexpr inline std::string WINDOW_NAME = "Heroes3App";

namespace {
void generateNoise() {
  FastNoiseLite noise{ 1337 };                                  // seed
  noise.SetNoiseType( FastNoiseLite::NoiseType_OpenSimplex2 );  // or NoiseType_OpenSimplex2S (smoother, slower)
  noise.SetFractalType( FastNoiseLite::FractalType_FBm );       // turns on fBm
  noise.SetFrequency( 0.005f );                                 // feature size: lower = bigger hills (default 0.01)
  noise.SetFractalOctaves( 6 );                                 // detail layers (default 3)
  noise.SetFractalLacunarity( 2.0f );                           // frequency multiplier per layer (default 2.0)
  noise.SetFractalGain( 0.5f );                                 // amplitude multiplier per layer (default 0.5)
  float value = noise.GetNoise( x, y );  // returns roughly -1..1; same x, y, seed always gives the same value
}
}  // namespace

int main() {
  sf::RenderWindow window{ sf::VideoMode{ sf::Vector2u{ static_cast<unsigned int>( graphics::WINDOW_WIDTH ),
                                                        static_cast<unsigned int>( graphics::WINDOW_HEIGHT ) } },
                           WINDOW_NAME, sf::Style::Titlebar | sf::Style::Close };
  window.setFramerateLimit( FRAMES_PER_SECOND );
  window.setPosition( sf::Vector2i{ 0, 0 } );

  sf::RenderTexture target;
  err::passCondOrAbort( target.resize( sf::Vector2u{ static_cast<unsigned int>( graphics::WINDOW_WIDTH ),
                                                     static_cast<unsigned int>( graphics::WINDOW_HEIGHT ) } ) );
  target.setSmooth( false );

  while ( window.isOpen() ) {
    WorldMap world_map = WorldMap{};

    if ( window.getSize()
         != sf::Vector2u( static_cast<unsigned int>( graphics::WINDOW_WIDTH ),
                          static_cast<unsigned int>( graphics::WINDOW_HEIGHT ) ) ) {
      window.setSize( { static_cast<unsigned int>( graphics::WINDOW_WIDTH ),
                        static_cast<unsigned int>( graphics::WINDOW_HEIGHT ) } );
      window.setView( sf::View{ sf::FloatRect{ { 0.F, 0.F }, sf::Vector2f{ window.getSize() } } } );
    }

    while ( std::optional event = window.pollEvent() ) {
      if ( event->is<sf::Event::Closed>() ) {
        window.close();
        return 0;
      }
      if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Q ) ) {
      }
    }
    MapRenderer{ window, target, game }.render();
  }
};