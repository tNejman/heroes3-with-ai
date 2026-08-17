#include "Graphics/SpriteVisitor.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cassert>
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Artifact/Artifact.h"
#include "Battle/Moves/Move.hpp"
#include "Battle/Obstacle.h"
#include "Character/Character.h"
#include "Character/SecondarySkill.h"
#include "Exceptions/BadCopyException.hpp"
#include "Exceptions/Err.hpp"
#include "Exceptions/InvalidSecondarySkillException.hpp"
#include "Exceptions/InvalidTextureException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Graphics/Visitor.h"
#include "Magic/Spell.h"
#include "Miscellaneous/CharacterLib.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "Resource/Resource.h"
#include "Unit/Unit.h"
#include "Unit/UnitStack.h"
#include "WorldMap/Building.h"
#include "WorldMap/OverworldObstacle.h"

// Nazwa przedmiotu jako path do Sprita
//
//====================================

sf::Texture& SpriteVisitor::visit( const Artifact& e [[maybe_unused]] ) {
  // std::string path = "Sprites/artifacts/" + e.getName() + ".png";
  // return findTexture( path );
  err::raise<NotImplementedException>( "" );  // TODO
}

sf::Texture& SpriteVisitor::visit( const Obstacle& e ) {
  std::string path = "Sprites/obstacles/" + e.getName() + ".png";
  return findTexture( path );
}

sf::Texture& SpriteVisitor::visit( const Character& e ) {
  std::string path = "Sprites/heroes/";
  path += CHARACTER_TYPE_TO_STRING.find( e.getCharacterType() )->second;
  path += CHARACTER_ORIENTATION_TO_STRING.find( e.getOrientation() )->second;
  path += ".png";
  sf::Texture& tex_temp = findTexture( path );
  assert( tex_temp.getSize().x == 95 );
  assert( tex_temp.getSize().y == 64 );
  return tex_temp;
}

sf::Texture& SpriteVisitor::visit( const SecondarySkill& e ) {
  std::string secondary_skill_name;
  switch ( e.getType() ) {
    case SecondarySkillType::AIR_MAGIC: secondary_skill_name = "Air Magic"; break;
    case SecondarySkillType::FIRE_MAGIC: secondary_skill_name = "Fire Magic"; break;
    case SecondarySkillType::EARTH_MAGIC: secondary_skill_name = "Earth Magic"; break;
    case SecondarySkillType::WATER_MAGIC: secondary_skill_name = "Water Magic"; break;
  }
  if ( secondary_skill_name == "" ) {
    err::raise<InvalidSecondarySkillException>( "Tried to fetch sprite but encountered invalid SecondarySkillType: "
                                                + std::to_string( static_cast<int>( e.getType() ) ) );
  }

  std::string path = "Sprites/Secondaryskills/" + secondary_skill_name + "_"
                     + std::to_string( static_cast<int>( e.getLevel() ) ) + ".png";
  return findTexture( path );
}

sf::Texture& SpriteVisitor::visit( const Spell& e ) {
  std::string path = "Sprites/spells/" + e.getName() + ".png";
  return findTexture( path );
}

// sf::Texture& SpriteVisitor::visit(const SpellBook& e) {
//     std::string path = "Sprites/spellbooks/Spellbook.png";
//     return FindTexture(path);
// }

// sf::Texture& SpriteVisitor::visit( const UnitStack& e ) {
//   std::string path = "Sprites/units/" + e.getData().name_ + ".png";
//   return findTexture( path );
// }

sf::Texture& SpriteVisitor::visit( const Resource& e ) {
  std::string resource_name;
  switch ( e.getType() ) {
    case ResourceType::TIMBER: resource_name = "Timber"; break;
    case ResourceType::MERCURY: resource_name = "Mercury"; break;
    case ResourceType::STONE: resource_name = "Stone"; break;
    case ResourceType::SULFUR: resource_name = "Sulfur"; break;
    case ResourceType::CRYSTAL: resource_name = "Crystal"; break;
    case ResourceType::GEMSTONE: resource_name = "Gemstone"; break;
    case ResourceType::MONEY: resource_name = "Money"; break;
  }

  std::string path = "Sprites/resources/" + resource_name + ".png";
  return findTexture( path );
}

sf::Texture& SpriteVisitor::visit( const Building& e ) {
  std::string path = "Sprites/buildings/" + e.getName() + ".png";
  return findTexture( path );
}

sf::Texture& SpriteVisitor::visit( const Terrain& e ) {
  std::string sprite_name;
  switch ( e ) {
    case Terrain::GRASS: sprite_name = "tgrb000"; break;
    case Terrain::DIRT: sprite_name = "tdtb000"; break;
    case Terrain::MOSTLY_GRASS: sprite_name = "tgrb022"; break;
    case Terrain::ROCKS: sprite_name = "trob000"; break;
    case Terrain::ROCKS_CRUSHED: sprite_name = "trob024"; break;
    case Terrain::SAND: sprite_name = "tsub000"; break;
    default: err::raise<InvalidTextureException>( "Unknown terrain type" );
  }
  const std::string path = "Sprites/terrain/tiles/" + sprite_name + ".png";
  sf::Texture& tex_temp = findTexture( path );
  assert( tex_temp.getSize().x == 32 );
  assert( tex_temp.getSize().y == 32 );
  return tex_temp;
}

sf::Texture& SpriteVisitor::visit( const OverworldObstacle& e ) {
  std::string path = "Sprites/terrain/Overworld_obstacles/" + e.getName() + ".png";
  sf::Texture& tex_temp = findTexture( path );
  assert( tex_temp.getSize().x == 32 );
  assert( tex_temp.getSize().y == 32 );
  return findTexture( path );
}

// sf::Texture& SpriteVisitor::visit(const WorldMap& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Player& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Castle& e) @TODO

sf::Texture& SpriteVisitor::visit( const Battle& e ) {
  // CmBkDrTr.png
  sf::Image combined_image;
  std::string path = "Sprites/Battle_Backgrounds/CmBkDrTr.png";
  if ( !combined_image.loadFromFile( path ) ) {
    err::raise<std::runtime_error>( "Failed to load battle background image: " + path );
  }
  const auto units_sorted = e.getUnitsInBattleSortedToPrint();
  const auto units_defender = e.getDefendingArmy();

  std::pair<sf::Texture, std::string> pair_image = getBattleHexagons( e.getPossibleMoves() );
  sf::Image image_hex = pair_image.first.copyToImage();
  path += pair_image.second;
  (void)combined_image.copy( image_hex, sf::Vector2u( 0, 0 ), sf::IntRect(), true );

  for ( const UnitStack& unit : units_sorted ) {
    CoordPair unit_coords = unit.getCoordsInBattle();
    int offset_x = 0;
    int offset_y = 0;
    offset_x = BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD + ( unit_coords.x_ * BATTLE_MAP_SPRITE_X_DELTA );
    offset_y =
        BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD_UNIT + ( ( 4 - ( unit_coords.y_ / 2 ) ) * BATTLE_MAP_SPRITE_Y_DELTA );
    if ( unit_coords.y_ % 2 == 0 ) {
      offset_x += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
      offset_y += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
    }
    sf::Image image_tmp;
    if ( !image_tmp.loadFromFile( "Sprites/units/" + unit.getData().name_ + ".png" ) ) {
      err::raise<std::runtime_error>( "Failed to load image: Sprites/units/" + unit.getData().name_ + ".png" );
    }
    if ( std::ranges::find_if( units_defender, [&]( const UnitStack& stack ) { return &stack == &unit; } )
         != units_defender.end() ) {
      image_tmp.flipHorizontally();
    }
    (void)combined_image.copy(
        image_tmp, sf::Vector2u( static_cast<unsigned int>( offset_x ), static_cast<unsigned int>( offset_y ) ),
        sf::IntRect(), true );
    path += "unit" + unit.getData().name_ + std::to_string( unit.getCoordsInBattle().x_ )
            + std::to_string( unit.getCoordsInBattle().y_ );
  }

  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    err::raise<std::runtime_error>( "Failed to load texture from image" );
  }
  if ( !textures_.contains( path ) ) {
    textures_.emplace( path, combined_texture );
  }

  return textures_[path];
}

sf::Texture& SpriteVisitor::findTexture( const std::string& path ) {
  if ( !textures_.contains( path ) ) {
    sf::Texture texture;
    if ( !texture.loadFromFile( path ) ) {
      err::raise<std::runtime_error>( "Failed to load texture from " + path );
    }
    textures_.emplace( path, texture );
  }
  return textures_[path];
}

sf::Image SpriteVisitor::mirrorImageHorizontally( const sf::Image& original ) const {
  sf::Vector2u size = original.getSize();
  sf::Image flipped( { size.x, size.y }, sf::Color::Transparent );

  for ( unsigned int y = 0; y < size.y; ++y ) {
    for ( unsigned int x = 0; x < size.x; ++x ) {
      flipped.setPixel( { size.x - 1 - x, y }, original.getPixel( { x, y } ) );
    }
  }

  return flipped;
}

std::pair<sf::Texture&, std::string> SpriteVisitor::getBattleHexagons( std::vector<std::shared_ptr<Move>> moves ) {
  sf::Image combined_image;
  std::string path_org = "Sprites/Battle_Backgrounds/CmBkDrTr.png";
  if ( !combined_image.loadFromFile( path_org ) ) {
    err::raise<std::runtime_error>( "Failed to load battle background image: " + path_org );
  }
  std::string path;
  for ( int x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( int y = 0; y < MAP_HEIGHT_BF; ++y ) {
      CoordPair map_tile_coord{ x, y };
      int offset_x_temp = 0;
      int offset_y_temp = 0;
      // set offset for even rows
      offset_x_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD + ( x * BATTLE_MAP_SPRITE_X_DELTA );
      offset_y_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD + ( ( 5 - ( y / 2 ) ) * BATTLE_MAP_SPRITE_Y_DELTA );

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }

      sf::Image image_hexagon;
      std::shared_ptr<Move> move_to_print;
      if ( moves.end() != std::ranges::find_if( moves, [&]( const std::shared_ptr<Move>& move ) {
             move_to_print = move;
             return move->destinationCoords() == map_tile_coord;
           } ) ) {
        if ( !image_hexagon.loadFromFile( move_to_print->getPath() ) ) {
          err::raise<std::runtime_error>( "Failed to load image: " + move_to_print->getPath() );
        }
        path += move_to_print->getPath();
      } else {
        if ( !image_hexagon.loadFromFile( HEXAGON_SPRITE_DEFAULT_PATH ) ) {
          err::raise<std::runtime_error>( "Failed to load image: " + HEXAGON_SPRITE_DEFAULT_PATH );
        }
        path += "n";
      }
      try {
        (void)combined_image.copy(
            image_hexagon,
            sf::Vector2u( static_cast<unsigned int>( offset_x_temp ), static_cast<unsigned int>( offset_y_temp ) ),
            sf::IntRect(), true );
      } catch ( const std::exception& e ) {
        err::raise<BadCopyException>( "hex creation failed" );
      }
    }
  }
  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    err::raise<std::runtime_error>( "Failed to load textur from image" );
  }
  textures_.emplace( path, combined_texture );

  return std::pair<sf::Texture&, std::string>( textures_[path], path );
}
