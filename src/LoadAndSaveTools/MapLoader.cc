#include "LoadAndSaveTools/MapLoader.h"

#include <cassert>
#include <memory>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/WorldMap.h"

void MapLoader::resetCounters() {
  x_counter_ = 0;
  y_counter_ = WORLD_MAP_HEIGHT - 1;
}

void MapLoader::moveWordToContainer( const int word ) {
  // for explanation look in header
  if ( x_counter_ >= WORLD_MAP_WIDTH || y_counter_ >= WORLD_MAP_HEIGHT ) {
    throw CoordinateOutOfBoundsException( "MapLoader exceeds WorldMap coordinates" );
  }
  container_[x_counter_][y_counter_] = word;

  ++x_counter_;
  if ( x_counter_ == WORLD_MAP_WIDTH ) {
    x_counter_ = 0;
    --y_counter_;
  }
}

std::shared_ptr<WorldMap> MapLoader::getObjectFromContainer() {
  // for explanation look in header
  assert( y_counter_ == 4'294'967'295 );
  assert( x_counter_ == 0 );
  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>();
  world_map->loadGrid( container_ );
  return world_map;
}
