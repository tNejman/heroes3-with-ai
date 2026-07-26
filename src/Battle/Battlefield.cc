#include "Battle/BattleField.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Battle/Tile.h"
#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

BattleField::BattleField( std::shared_ptr<GridTile> background ) : background_( background ) {
  for ( auto& col : battle_grid_ ) {
    for ( auto& tile_ptr : col ) {
      tile_ptr = nullptr;
    }
  }
};

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const CoordPair coords ) {
  const uint32_t x = coords.x_;
  const uint32_t y = coords.y_;

  const auto& directions = ( y % 2 == 0 ) ? EVEN_DIRECTIONS_BATTLE : ODD_DIRECTIONS_BATTLE;
  std::vector<std::shared_ptr<Tile>> neighbours;

  for ( const ShiftPair& delta : directions ) {
    int nx = (int)x + delta.dx_;
    int ny = (int)y + delta.dy_;

    if ( nx >= 0 && nx < (int)MAP_WIDTH_BF && ny >= 0 && ny < (int)MAP_HEIGHT_BF ) {
      const auto& tile_ptr = getTileByProxy( CoordPair( uint32_t( nx ), uint32_t( ny ) ) );
      neighbours.push_back( tile_ptr );
    } else {
      neighbours.push_back( nullptr );
    }
  }

  return neighbours;
};

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const std::shared_ptr<Tile> tile ) {
  return getTileNeighbours( tile->getCoords() );
}

std::shared_ptr<Tile> BattleField::getTileByProxy( CoordPair coords ) {
  uint32_t x = coords.x_;
  uint32_t y = coords.y_;
  if ( x >= MAP_WIDTH_BF || y >= MAP_HEIGHT_BF ) {
    std::string exc_mess = "Battlefield::getTileByProxy exceeds battlefield cooridnates: x=";
    exc_mess += std::to_string( x ) + " y=" + std::to_string( y );
    throw CoordinateOutOfBoundsException( exc_mess );
  }
  if ( battle_grid_[x][y] == nullptr ) {
    battle_grid_[x][y] = std::make_shared<Tile>( coords );
  };
  return battle_grid_[x][y];
}

std::vector<CoordPair> BattleField::getCoordPairs( CoordPair coords ) {
  uint32_t x = coords.x_;
  uint32_t y = coords.y_;
  std::vector<CoordPair> tmp;
  if ( !( y % 2 ) ) {
    if ( y < (int)MAP_HEIGHT_BF - 1 && x < (int)MAP_WIDTH_BF - 1 ) tmp.push_back( CoordPair( x + 1, y + 1 ) );
    if ( x < (int)MAP_WIDTH_BF - 1 ) tmp.push_back( CoordPair( x + 1, y ) );
    if ( y > 0 && x < (int)MAP_WIDTH_BF - 1 ) tmp.push_back( CoordPair( x + 1, y - 1 ) );
    if ( y > 0 ) tmp.push_back( CoordPair( x, y - 1 ) );
    if ( x > 0 ) tmp.push_back( CoordPair( x - 1, y ) );
    if ( y < (int)MAP_HEIGHT_BF - 1 ) tmp.push_back( CoordPair( x, y + 1 ) );
  } else {
    if ( y < (int)MAP_HEIGHT_BF - 1 ) tmp.push_back( CoordPair( x, y + 1 ) );
    if ( x < (int)MAP_WIDTH_BF - 1 ) tmp.push_back( CoordPair( x + 1, y ) );
    if ( y > 0 ) tmp.push_back( CoordPair( x, y - 1 ) );
    if ( x > 0 && y > 0 ) tmp.push_back( CoordPair( x - 1, y - 1 ) );
    if ( x > 0 ) tmp.push_back( CoordPair( x - 1, y ) );
    if ( x > 0 && y < (int)MAP_HEIGHT_BF - 1 ) tmp.push_back( CoordPair( x - 1, y + 1 ) );
  }
  return tmp;
}

std::shared_ptr<GridTile> BattleField::getBackground() {
  return background_;
}

void BattleField::eraseEmptyTiles() {
  for ( auto& col : battle_grid_ ) {
    for ( auto& tile_ptr : col ) {
      if ( tile_ptr->getObject() == nullptr ) {
        tile_ptr.reset();
      }
    }
  }
}