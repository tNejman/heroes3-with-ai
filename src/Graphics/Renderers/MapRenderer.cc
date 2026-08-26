#include "Graphics/Renderers/MapRenderer.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Artifact/Artifact.h"
#include "Character/Character.h"
#include "Exceptions/Err.hpp"
#include "Exceptions/NotOpenWindowException.hpp"
#include "Graphics/Renderers/IRenderer.hpp"
#include "Graphics/SpriteFactory.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

void MapRenderer::renderGrid() {
  int center_x = center_coords_.x_;
  int center_y = center_coords_.y_;

  for ( int x = 0; x < WORLD_MAP_WIDTH; ++x ) {
    for ( int y = 0; y < WORLD_MAP_HEIGHT; ++y ) {
      const auto terrain = object_.get().getTerrain( { x, y } );

      double screen_x =
          ( ( x - center_x ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2 );
      double screen_y =
          ( ( center_y - y ) * TERRAIN_SPRITE_HEIGHT ) + ( static_cast<double>( window_.get().getSize().y ) / 2 );

      sf::Sprite sprite = SpriteFactory::getSpriteFromBindingV( Tagged<Terrain, SpriteDomain::WORLD>{ terrain } );
      sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
      if ( window_.get().isOpen() ) {
        window_.get().draw( sprite );
      } else {
        err::raise<NotOpenWindowException>( "Tried to render with no window open" );
      }
    }
  }
}

void MapRenderer::renderObjects() {
  // This method iterates through the grid again to terrain overlapping sprites
  int center_x = center_coords_.x_;
  int center_y = center_coords_.y_;

  for ( int x = 0; x < WORLD_MAP_WIDTH; ++x ) {
    for ( int y = 0; y < WORLD_MAP_HEIGHT; ++y ) {
      const auto* const map_obj = object_.get().getMapObject( { x, y } );
      if ( map_obj == nullptr ) {
        continue;
      }
      if ( dynamic_cast<const Character*>( map_obj ) != nullptr ) {
        double screen_x =
            ( ( x - center_x ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2.0 );
        double screen_y =
            ( ( center_y - y ) * TERRAIN_SPRITE_HEIGHT ) + ( static_cast<double>( window_.get().getSize().y ) / 2.0 );

        map_obj->accept( *sprite_visitor );
        sf::Sprite sprite_map_obj( sprite_visitor->extractSprite() );
        sprite_map_obj.setTextureRect(
            sf::IntRect( { 0, 0 }, { HERO_SPRITE_WIDTH_DEPRECATED, HERO_SPRITE_HEIGHT_DEPRECATED } ) );
        sprite_map_obj.setOrigin( sf::Vector2f( static_cast<float>( HERO_SPRITE_WIDTH_DEPRECATED ) / 2.F,
                                                static_cast<float>( HERO_SPRITE_HEIGHT_DEPRECATED ) ) );
        sprite_map_obj.setPosition(
            sf::Vector2f( static_cast<float>( screen_x ) + ( static_cast<float>( TERRAIN_SPRITE_WIDTH ) / 2.F ),
                          static_cast<float>( screen_y ) + static_cast<float>( TERRAIN_SPRITE_HEIGHT ) ) );
        if ( window_.get().isOpen() ) {
          window_.get().draw( sprite_map_obj );
        } else {
          err::raise<NotOpenWindowException>( "Tried to render with no window open" );
        }
      } else if ( const auto* obstacle_ptr = dynamic_cast<const OverworldObstacle*>( map_obj ) ) {
        double screen_x =
            ( ( x - center_x ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2 );
        double screen_y =
            ( ( center_y - y ) * TERRAIN_SPRITE_HEIGHT ) + ( static_cast<double>( window_.get().getSize().y ) / 2 );

        obstacle_ptr->accept( *sprite_visitor );
        sf::Sprite sprite( sprite_visitor->extractSprite() );
        sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
        if ( window_.get().isOpen() ) {
          window_.get().draw( sprite );
        } else {
          err::raise<NotOpenWindowException>( "Tried to render with no window open" );
        }
      } else if ( const auto* artifact_ptr = dynamic_cast<const Artifact*>( map_obj ) ) {
        double screen_x =
            ( ( x - center_x ) * TERRAIN_SPRITE_WIDTH ) + ( static_cast<double>( window_.get().getSize().x ) / 2 );
        double screen_y =
            ( ( center_y - y ) * TERRAIN_SPRITE_HEIGHT ) + ( static_cast<double>( window_.get().getSize().y ) / 2 );

        artifact_ptr->accept( *sprite_visitor );
        sf::Sprite sprite( sprite_visitor->extractSprite() );
        sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
        if ( window_.get().isOpen() ) {
          window_.get().draw( sprite );
        } else {
          err::raise<NotOpenWindowException>( "Tried to render with no window open" );
        }
      }
    }
  }
}

/* === @PUBLIC === */
MapRenderer::MapRenderer( sf::RenderWindow& window, const WorldMap& object, CoordPair center_coords )
    : IRenderer( window, object ), center_coords_( center_coords ) {
}

void MapRenderer::render() {
  renderGrid();
  renderObjects();
}
