#include "LoadAndSaveTools/MapLoader.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <memory>
#include <vector>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

void MapLoader::resetCounters() {
  x_counter_ = 0;
  y_counter_ = WORLD_MAP_HEIGHT - 1;
}

void MapLoader::moveWordToContainer( const int word ) {
  // for explanation look in header
  if ( x_counter_ >= WORLD_MAP_WIDTH || y_counter_ >= WORLD_MAP_HEIGHT ) {
    err::raise<CoordinateOutOfBoundsException>( "MapLoader exceeds WorldMap coordinates" );
  }
  container_[x_counter_][y_counter_] = word;

  ++x_counter_;
  if ( x_counter_ == WORLD_MAP_WIDTH ) {
    x_counter_ = 0;
    --y_counter_;
  }
}

WorldMap MapLoader::getObjectFromContainer() {
  // for explanation look in header
  assert( y_counter_ == 4'294'967'295 );
  assert( x_counter_ == 0 );
  return WorldMap{ container_, generateObstacles() };
  ;
}

std::vector<std::shared_ptr<OverworldObstacle>> MapLoader::generateObstacles() {
  const uint32_t obstacle_count = 1'000U;
  std::vector<std::shared_ptr<OverworldObstacle>> obstacles;
  double step = std::sqrt( ( WORLD_MAP_WIDTH * WORLD_MAP_HEIGHT ) / static_cast<double>( obstacle_count ) );
  uint32_t count = 0;
  for ( double y = step / 2; y < WORLD_MAP_HEIGHT && count < obstacle_count; y += step ) {
    for ( double x = step / 2; x < WORLD_MAP_WIDTH && count < obstacle_count; x += step ) {
      auto x_loc = static_cast<int>( x );
      auto y_loc = static_cast<int>( y );
      // if ( int( x * y ) % 3 == 0 )
      // obstacles.push_back( std::make_shared<OverworldObstacle>( "AVLs11s0", CoordPair( x_loc, y_loc ) ) );
      if ( int( x * y ) % 2 == 0 ) {
        obstacles.push_back( std::make_shared<OverworldObstacle>( OverworldObstacleType::DRIED_TREE,
                                                                  CoordPair( x_loc, y_loc ) ) );  // dried tree
      } else {
        obstacles.push_back( std::make_shared<OverworldObstacle>( OverworldObstacleType::GREEN_TREE,
                                                                  CoordPair( x_loc, y_loc ) ) );  // green tree
      }
    }
  }
  return obstacles;
}