#include "Graphics/Renderers/MapRenderer.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <memory>

#include "Artifact/Artifact.h"
#include "Character/Character.h"
#include "Exceptions/NotOpenWindowException.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"


void MapRenderer::render( sf::RenderWindow& window, const CoordPair center_coords ) {
  renderGrid( window, center_coords );
  renderObjects( window, center_coords );
}

void MapRenderer::renderGrid( sf::RenderWindow& window, const CoordPair center_coords ) {
  uint32_t center_x = center_coords.x_;
  uint32_t center_y = center_coords.y_;

  for ( uint32_t x = 0; x < WORLD_MAP_WIDTH; ++x ) {
    for ( uint32_t y = 0; y < WORLD_MAP_HEIGHT; ++y ) {
      const auto tile = object_->getTile( CoordPair( x, y ) );
      const auto map_obj = tile->getMapObject();
      const auto terrain = tile->getTerrain();

      double screen_x = ( x - center_x ) * TERRAIN_SPRITE_WIDTH + window.getSize().x / 2;
      double screen_y = ( center_y - y ) * TERRAIN_SPRITE_HEIGHT + window.getSize().y / 2;

      // sprite visitor has to visit explicitly, because terrain is not a class but enum
      sf::Sprite sprite( sprite_visitor_->visit( terrain ) );
      sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
      if ( window.isOpen() )
        window.draw( sprite );
      else
        throw NotOpenWindowException( "Tried to render with no window open" );
    }
  }
}

void MapRenderer::renderObjects( sf::RenderWindow& window, const CoordPair center_coords ) {
  // This method iterates through the grid again to terrain overlapping sprites
  uint32_t center_x = center_coords.x_;
  uint32_t center_y = center_coords.y_;

  for ( uint32_t x = 0; x < WORLD_MAP_WIDTH; ++x ) {
    for ( uint32_t y = 0; y < WORLD_MAP_HEIGHT; ++y ) {
      const auto tile = object_->getTile( CoordPair( x, y ) );
      const auto map_obj = tile->getMapObject();
      if ( map_obj == nullptr ) {
        continue;
      } else if ( auto character_ptr = std::dynamic_pointer_cast<Character>( map_obj ) ) {
        double screen_x = ( x - center_x ) * TERRAIN_SPRITE_WIDTH + window.getSize().x / 2;
        double screen_y = ( center_y - y ) * TERRAIN_SPRITE_HEIGHT + window.getSize().y / 2;

        sf::Sprite sprite_map_obj( map_obj->accept( *sprite_visitor_ ) );
        sprite_map_obj.setTextureRect( sf::IntRect( { 0, 0 }, { HERO_SPRITE_WIDTH, HERO_SPRITE_HEIGHT } ) );
        sprite_map_obj.setOrigin( sf::Vector2f( float( HERO_SPRITE_WIDTH ) / 2.f, float( HERO_SPRITE_HEIGHT ) ) );
        sprite_map_obj.setPosition( sf::Vector2f( float( screen_x ) + float( TERRAIN_SPRITE_WIDTH ) / 2.f,
                                                  float( screen_y ) + float( TERRAIN_SPRITE_HEIGHT ) ) );
        if ( window.isOpen() )
          window.draw( sprite_map_obj );
        else
          throw NotOpenWindowException( "Tried to render with no window open" );
      } else if ( auto obstacle_ptr = std::dynamic_pointer_cast<OverworldObstacle>( map_obj ) ) {
        double screen_x = ( x - center_x ) * TERRAIN_SPRITE_WIDTH + window.getSize().x / 2;
        double screen_y = ( center_y - y ) * TERRAIN_SPRITE_HEIGHT + window.getSize().y / 2;

        sf::Sprite sprite( obstacle_ptr->accept( *sprite_visitor_ ) );
        sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
        if ( window.isOpen() )
          window.draw( sprite );
        else
          throw NotOpenWindowException( "Tried to render with no window open" );
      } else if ( auto artifact_ptr = std::dynamic_pointer_cast<Artifact>( map_obj ) ) {
        double screen_x = ( x - center_x ) * TERRAIN_SPRITE_WIDTH + window.getSize().x / 2;
        double screen_y = ( center_y - y ) * TERRAIN_SPRITE_HEIGHT + window.getSize().y / 2;

        sf::Sprite sprite( artifact_ptr->accept( *sprite_visitor_ ) );
        sprite.setPosition( sf::Vector2f( float( screen_x ), float( screen_y ) ) );
        if ( window.isOpen() )
          window.draw( sprite );
        else
          throw NotOpenWindowException( "Tried to render with no window open" );
      }
    }
  }
}
