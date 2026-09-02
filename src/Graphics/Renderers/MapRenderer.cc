#include "Graphics/Renderers/MapRenderer.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <iostream>

#include "Exceptions/Err.hpp"
#include "Graphics/Renderers/IRenderer.hpp"
#include "Graphics/SpriteFactory.h"
#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/WorldMap.h"

void MapRenderer::renderGridWithFun( void ( MapRenderer::*fun )( int, int ) const ) const noexcept {
  static constexpr int MAX_TILES_VISIBLE_FROM_CENTER_HORIZONTALLY = 13;
  static constexpr int MAX_TILES_VISIBLE_FROM_CENTER_VERTICALLY = 11;

  int center_x = center_coords_.x_;
  int center_y = center_coords_.y_;

  int max_left_visible_tile_x = std::max( 0, center_x - MAX_TILES_VISIBLE_FROM_CENTER_HORIZONTALLY );
  int max_right_visible_tile_x = std::min( WORLD_MAP_WIDTH, center_x + MAX_TILES_VISIBLE_FROM_CENTER_HORIZONTALLY );

  int max_bottom_visible_tile_y = std::max( 0, center_y - MAX_TILES_VISIBLE_FROM_CENTER_VERTICALLY );
  int max_top_visible_tile_y = std::min( WORLD_MAP_HEIGHT, center_y + MAX_TILES_VISIBLE_FROM_CENTER_VERTICALLY );

  for ( int x = max_left_visible_tile_x; x < max_right_visible_tile_x; ++x ) {
    for ( int y = max_bottom_visible_tile_y; y < max_top_visible_tile_y; ++y ) {
      ( *this.*fun )( x, y );
    }
  }
}

void MapRenderer::renderBackgroundTile( int x, int y ) const noexcept {
  const auto terrain = object_.get().getTerrain( { x, y } );

  double screen_x =
      ( ( x - center_coords_.x_ ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2 );
  double screen_y =
      ( ( center_coords_.y_ - y ) * TERRAIN_SPRITE_HEIGHT ) + ( static_cast<double>( window_.get().getSize().y ) / 2 );

  sf::Sprite sprite = SpriteFactory::getSpriteFromBindingV( Tagged<Terrain, SpriteDomain::WORLD>{ terrain } );
  sprite.setPosition( sf::Vector2f{ static_cast<float>( screen_x ), static_cast<float>( screen_y ) } );

  err::passCondOrAbort( window_.get().isOpen(), "Tried to render with no window open" );

  window_.get().draw( sprite );
}

void MapRenderer::renderObject( int x, int y ) const noexcept {
  const auto* const map_obj = object_.get().getMapObject( { x, y } );
  if ( map_obj == nullptr ) {
    return;
  }
  map_obj->accept( *sprite_visitor );
  sf::Sprite sprite_map_obj = sprite_visitor->extractSprite();

  double screen_x =
      ( ( x - center_coords_.x_ ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2.0 );
  double screen_y = ( ( center_coords_.y_ - y ) * TERRAIN_SPRITE_HEIGHT )
                    + ( static_cast<double>( window_.get().getSize().y ) / 2.0 );
  sprite_map_obj.setOrigin( sf::Vector2f{ static_cast<float>( sprite_map_obj.getTextureRect().size.x ) / 2.F,
                                          static_cast<float>( sprite_map_obj.getTextureRect().size.y ) } );
  sprite_map_obj.setPosition(
      sf::Vector2f{ static_cast<float>( screen_x ) + ( static_cast<float>( TERRAIN_SPRITE_WIDTH ) / 2.F ),
                    static_cast<float>( screen_y ) + static_cast<float>( TERRAIN_SPRITE_HEIGHT ) } );
  window_.get().draw( sprite_map_obj );
}

/* === @PUBLIC === */
MapRenderer::MapRenderer( sf::RenderWindow& window, const WorldMap& object, CoordPair center_coords )
    : IRenderer( window, object ), center_coords_( center_coords ) {
}

void MapRenderer::render() {
  renderGridWithFun( &MapRenderer::renderBackgroundTile );
  renderGridWithFun( &MapRenderer::renderObject );
}
