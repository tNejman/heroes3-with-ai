#include "Graphics/Renderers/GameRenderer.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

#include "Exceptions/Err.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Game/Game.h"
#include "Graphics/Renderers/IRenderer.hpp"
#include "Graphics/Renderers/MapRenderer.h"
#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

GameRenderer::GameRenderer( const Game& game ) : IRenderer<Game>( std::make_shared<SpriteVisitor>(), game ) {
}

void GameRenderer::render( sf::RenderWindow& window, CoordPair center_coords ) {
  switch ( object_.get().getState() ) {
    case GameState::OVERWORLD: {
      MapRenderer{ sprite_visitor_, object_.get().getMap() }.render( window, center_coords );
      return;
    }
    case GameState::BATTLE: {
      sf::Sprite s{ object_.get().getBattle().accept( *sprite_visitor_ ) };
      window.draw( s );
      return;
    }
    case GameState::MENU: {
      err::raise<NotImplementedException>( "GameState::MENU" );
    }
  }
}