#include "Battle/BattleField.h"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Battle/Tile.h"
#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

BattleField::BattleField( std::shared_ptr<GridTile> background )
    : battle_grid_(), background_( std::move( background ) ) {};

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const CoordPair coords ) {
  const int x = coords.x_;
  const int y = coords.y_;

  const auto& directions = ( y % 2 == 0 ) ? EVEN_DIRECTIONS_BATTLE : ODD_DIRECTIONS_BATTLE;
  std::vector<std::shared_ptr<Tile>> neighbours;

  for ( const ShiftPair& delta : directions ) {
    int nx = (int)x + delta.dx_;
    int ny = (int)y + delta.dy_;

    if ( nx >= 0 && nx < (int)MAP_WIDTH_BF && ny >= 0 && ny < (int)MAP_HEIGHT_BF ) {
      const auto& tile_ptr = getTileByProxy( CoordPair{ nx, ny } );
      neighbours.push_back( tile_ptr );
    } else {
      neighbours.push_back( nullptr );
    }
  }

  return neighbours;
};

std::vector<std::shared_ptr<Tile>> BattleField::getTileNeighbours( const std::shared_ptr<Tile>& tile ) {
  return getTileNeighbours( tile->getCoords() );
}

std::shared_ptr<Tile> BattleField::getTileByProxy( CoordPair coords ) {
  if ( coords.x_ >= MAP_WIDTH_BF || coords.y_ >= MAP_HEIGHT_BF || coords.x_ < 0 || coords.y_ < 0 ) {
    std::string exc_mess = "exceeded battlefield cooridnates: x=";
    exc_mess += std::to_string( coords.x_ ) + " y=" + std::to_string( coords.y_ );
    err::raise<CoordinateOutOfBoundsException>( exc_mess );
  }
  auto x = static_cast<size_t>( coords.x_ );
  auto y = static_cast<size_t>( coords.y_ );
  if ( battle_grid_.at( x ).at( y ) == nullptr ) {
    battle_grid_.at( x ).at( y ) = std::make_shared<Tile>( coords );
  };
  return battle_grid_.at( x ).at( y );
}

std::vector<CoordPair> BattleField::getCoordPairs( CoordPair coords ) {
  int x = coords.x_;
  int y = coords.y_;
  std::vector<CoordPair> tmp;
  if ( y % 2 == 0U ) {
    if ( y < (int)MAP_HEIGHT_BF - 1 && x < (int)MAP_WIDTH_BF - 1 ) {
      tmp.push_back( CoordPair( x + 1, y + 1 ) );
    }
    if ( x < (int)MAP_WIDTH_BF - 1 ) {
      tmp.push_back( CoordPair( x + 1, y ) );
    }
    if ( y > 0 && x < (int)MAP_WIDTH_BF - 1 ) {
      tmp.push_back( CoordPair( x + 1, y - 1 ) );
    }
    if ( y > 0 ) {
      tmp.push_back( CoordPair( x, y - 1 ) );
    }
    if ( x > 0 ) {
      tmp.push_back( CoordPair( x - 1, y ) );
    }
    if ( y < (int)MAP_HEIGHT_BF - 1 ) {
      tmp.push_back( CoordPair( x, y + 1 ) );
    }
  } else {
    if ( y < (int)MAP_HEIGHT_BF - 1 ) {
      tmp.push_back( CoordPair( x, y + 1 ) );
    }
    if ( x < (int)MAP_WIDTH_BF - 1 ) {
      tmp.push_back( CoordPair( x + 1, y ) );
    }
    if ( y > 0 ) {
      tmp.push_back( CoordPair( x, y - 1 ) );
    }
    if ( x > 0 && y > 0 ) {
      tmp.push_back( CoordPair( x - 1, y - 1 ) );
    }
    if ( x > 0 ) {
      tmp.push_back( CoordPair( x - 1, y ) );
    }
    if ( x > 0 && y < (int)MAP_HEIGHT_BF - 1 ) {
      tmp.push_back( CoordPair( x - 1, y + 1 ) );
    }
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