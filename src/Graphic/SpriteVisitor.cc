#include "Graphic/SpriteVisitor.h"
// Nazwa przedmiotu jako path do Sprita
//
//====================================
sf::Texture& SpriteVisitor::visit( const Artifact& e ) {
  std::string path = "Sprites/artifacts/" + e.getName() + ".png";
  return FindTexture( path );
}
sf::Texture& SpriteVisitor::visit( const Obstacle& e ) {
  std::string path = "Sprites/obstacles/" + e.getName() + ".png";
  return FindTexture( path );
}
sf::Texture& SpriteVisitor::visit( const Character& e ) {
  std::string path = "Sprites/heroes/" + e.getName() + ".png";
  sf::Texture& tex_temp = FindTexture( path );
  assert( tex_temp.getSize().x == 95 );
  assert( tex_temp.getSize().y == 64 );
  return tex_temp;
}
sf::Texture& SpriteVisitor::visit( const SecondarySkill& e ) {
  std::string path = "Sprites/Secondaryskills/" + e.getName() + "_" + std::to_string( (int)e.getLevel() ) + ".png";
  return FindTexture( path );
}
sf::Texture& SpriteVisitor::visit( const Spell& e ) {
  std::string path = "Sprites/spells/" + e.getName() + ".png";
  return FindTexture( path );
}
// sf::Texture& SpriteVisitor::visit(const SpellBook& e) {
//     std::string path = "Sprites/spellbooks/Spellbook.png";
//     return FindTexture(path);
// }
sf::Texture& SpriteVisitor::visit( const Unit& e ) {
  std::string path = "Sprites/units/" + e.getName() + ".png";
  return FindTexture( path );
}
sf::Texture& SpriteVisitor::visit( const Resource& e ) {
  std::string path = "Sprites/resources/" + e.getName() + ".png";
  return FindTexture( path );
}
// sf::Texture& SpriteVisitor::visit(const Building& e) {
//     std::string path = "Sprites/buildings/" + e.getName() + ".png";
//     return FindTexture(path);
// }
sf::Texture& SpriteVisitor::visit( const Terrain& e ) {
  std::string sprite_name;
  switch ( e ) {
    case Terrain::GRASS:
      sprite_name = "tgrb000";
      break;
    case Terrain::DIRT:
      sprite_name = "tdtb000";
      break;
    case Terrain::MOSTLY_GRASS:
      sprite_name = "tgrb022";
      break;
    case Terrain::ROCKS:
      sprite_name = "trob000";
      break;
    case Terrain::ROCKS_CRUSHED:
      sprite_name = "trob024";
      break;
    case Terrain::SAND:
      sprite_name = "tsub000";
      break;
    default:
      throw InvalidTextureException( "Unknown terrain type" );
  }
  const std::string path = "Sprites/terrain/tiles/" + sprite_name + ".png";
  sf::Texture& tex_temp = FindTexture( path );
  assert( tex_temp.getSize().x == 32 );
  assert( tex_temp.getSize().y == 32 );
  return tex_temp;
}
sf::Texture& SpriteVisitor::visit( const OverworldObstacle& e ) {
  std::string path = "Sprites/terrain/Overworld_obstacles/" + e.getName() + ".png";
  sf::Texture& tex_temp = FindTexture( path );
  assert( tex_temp.getSize().x == 32 );
  assert( tex_temp.getSize().y == 32 );
  return FindTexture( path );
}

// sf::Texture& SpriteVisitor::visit(const WorldMap& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Player& e) @warning done in Renderer
// sf::Texture& SpriteVisitor::visit(const Castle& e) @TODO

sf::Texture& SpriteVisitor::visit( const Battle& e ) {
  // CmBkDrTr.png
  sf::Image combined_image;
  std::string path = "Sprites/Battle_Backgrounds/CmBkDrTr";
  if ( !combined_image.loadFromFile( "Sprites/Battle_Backgrounds/CmBkDrTr.png" ) ) {
    throw std::runtime_error( "Failed to load battle background image: Sprites/Battle_Backgrounds/CmBkDrTr.png" );
  }
  const auto units_sorted = e.getUnitsInBattleSortedToPrint();
  const auto units_defender = e.getDefendingArmy();

  std::pair<sf::Texture, std::string> pair_image = getBattleHexagons( e.getPossibleMoves() );
  sf::Image image_hex = pair_image.first.copyToImage();
  path += pair_image.second;
  (void)combined_image.copy( image_hex, sf::Vector2u( 0, 0 ), sf::IntRect(), true );

  for ( const auto& unit : units_sorted ) {
    CoordPair unit_coords = unit->getCoordsInBattle();
    uint32_t offset_x, offset_y;
    offset_x = BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD + unit_coords.x_ * BATTLE_MAP_SPRITE_X_DELTA;
    offset_y = BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD_UNIT + ( 4 - unit_coords.y_ / 2 ) * BATTLE_MAP_SPRITE_Y_DELTA;
    if ( unit_coords.y_ % 2 == 0 ) {
      offset_x += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
      offset_y += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
    }
    sf::Image image_tmp;
    if ( !image_tmp.loadFromFile( "Sprites/units/" + unit->getUnit()->getName() + ".png" ) ) {
      throw std::runtime_error( "Failed to load image: Sprites/units/" + unit->getUnit()->getName() + ".png" );
    }
    if ( std::find( units_defender.begin(), units_defender.end(), unit ) != units_defender.end() ) {
      image_tmp.flipHorizontally();
    }
    (void)combined_image.copy( image_tmp, sf::Vector2u( offset_x, offset_y ), sf::IntRect(), true );
    path = path + "unit" + unit->getUnit()->getName() + std::to_string( unit->getCoordsInBattle().x_ ) + std::to_string( unit->getCoordsInBattle().y_ );
  }

  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    throw std::runtime_error( "Failed to load texture from image" );
  }
  if ( textures_.find( path ) == textures_.end() ) {
    textures_.emplace( path, combined_texture );
  }

  return textures_[path];
}

sf::Texture& SpriteVisitor::FindTexture( const std::string& path ) {
  if ( textures_.find( path ) == textures_.end() ) {
    sf::Texture texture;
    if ( !texture.loadFromFile( path ) )
      throw std::runtime_error( "Failed to load texture from " + path );
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
  if ( !combined_image.loadFromFile( "Sprites/Battle_Backgrounds/CmBkDrTr.png" ) ) {
    throw std::runtime_error( "Failed to load battle background image: Sprites/Battle_Backgrounds/CmBkDrTr.png" );
  }
  std::string path = "";
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      CoordPair map_tile_coord( x, y );
      uint32_t offset_x_temp, offset_y_temp;
      // set offset for even rows
      offset_x_temp = BATTLE_MAP_SPRITE_INITAL_OFFSET_X_ODD + x * BATTLE_MAP_SPRITE_X_DELTA;
      offset_y_temp = BATTLE_MAP_SPRITE_INITAL_OFFSET_Y_ODD + ( 5 - y / 2 ) * BATTLE_MAP_SPRITE_Y_DELTA;

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }

      sf::Image image_hexagon;
      std::shared_ptr<Move> move_to_print;
      if ( moves.end() != std::find_if( moves.begin(), moves.end(), [&]( const std::shared_ptr<Move> move ) {move_to_print = move ; return move->destinationCoords() == map_tile_coord; } ) ) {
        if ( !image_hexagon.loadFromFile( move_to_print->getPath() ) ) {
          throw std::runtime_error( "Failed to load image: " + move_to_print->getPath() );
        }
        path += move_to_print->getPath();
      } else {
        if ( !image_hexagon.loadFromFile( HEXAGON_SPRITE_DEFAULT_PATH ) ) {
          throw std::runtime_error( "Failed to load image: " + HEXAGON_SPRITE_DEFAULT_PATH );
        }
        path += "n";
      }
      try {
        (void)combined_image.copy( image_hexagon, sf::Vector2u( offset_x_temp, offset_y_temp ), sf::IntRect(), true );
      } catch ( const std::exception& e ) {
        throw BadCopyException( "hex creation failed" );
      }
    }
  }
  sf::Texture combined_texture;
  if ( !combined_texture.loadFromImage( combined_image ) ) {
    throw std::runtime_error( "Failed to load textur from image" );
  }
  textures_.emplace( path, combined_texture );

  return std::pair<sf::Texture&, std::string>( textures_[path], path );
}
