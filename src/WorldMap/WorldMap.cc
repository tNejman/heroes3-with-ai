#include "WorldMap/WorldMap.h"

#include <array>
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"  // IWYU pragma: keep
#include "Exceptions/Err.hpp"
#include "Exceptions/InvalidMapMoveException.hpp"
#include "Game/IGameState.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Formatter.hpp"  // IWYU pragma: keep
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"

void WorldMap::loadBackground( const WorldMapGrid<int>& new_grid ) noexcept {
  // SINGLE_CALL_GUARD();
  for ( size_t col = 0; col < WORLD_MAP_WIDTH; ++col ) {
    for ( size_t row = 0; row < WORLD_MAP_HEIGHT; ++row ) {
      assert( new_grid[col][row] <= static_cast<int>( Terrain::COUNT ) && ( new_grid[col][row] >= 0 ) );
      background_[col][row] = static_cast<Terrain>( new_grid[col][row] );
    }
  }
}

void WorldMap::loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>> obstacles ) noexcept {
  // SINGLE_CALL_GUARD()
  for ( auto& obstacle : obstacles ) {
    setMapObject( obstacle->getCoords(), std::move( obstacle ) );
  }
}

/* === @PUBLIC === */

// omit zero initialization of array
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
WorldMap::WorldMap( const WorldMapGrid<int>& new_grid ) noexcept {
  WorldMap::loadBackground( new_grid );
}

WorldMap::WorldMap( const WorldMapGrid<int>& new_grid,
                    std::vector<std::shared_ptr<OverworldObstacle>> new_obstacles ) noexcept
    : WorldMap( new_grid ) {
  loadObstacles( std::move( new_obstacles ) );
}

bool WorldMap::areCoordsInBounds( CoordPair coords ) noexcept {
  return coords.x_ >= 0 && coords.x_ < WORLD_MAP_WIDTH && coords.y_ >= 0 && coords.y_ < WORLD_MAP_HEIGHT;
}

[[nodiscard]] Terrain WorldMap::getTerrain( CoordPair coords ) const noexcept {
  return background_[coords.xAsId()][coords.yAsId()];
}

[[nodiscard]] std::shared_ptr<MapObject>& WorldMap::getMapObjectShared( CoordPair coords ) noexcept {
  return foreground_[coords.xAsId()][coords.yAsId()];
}
[[nodiscard]] const MapObject* WorldMap::getMapObject( CoordPair coords ) const noexcept {
  return foreground_[coords.xAsId()][coords.yAsId()].get();
}
[[nodiscard]] MapObject* WorldMap::getMapObject( CoordPair coords ) noexcept {
  return foreground_[coords.xAsId()][coords.yAsId()].get();
}

void WorldMap::setMapObject( CoordPair coords, std::shared_ptr<MapObject> object ) noexcept {
  foreground_[coords.xAsId()][coords.yAsId()] = std::move( object );
}
void WorldMap::resetMapObject( CoordPair coords ) noexcept {
  foreground_[coords.xAsId()][coords.yAsId()].reset();
}

StateTransition WorldMap::moveMapObject( CoordPair old_coords, CoordPair new_coords ) {
  if ( old_coords == new_coords ) {
    return NoTransition{};
  }
  COORDS_IN_BOUNDS_OR_THROW( old_coords, "Origin: " );
  COORDS_IN_BOUNDS_OR_THROW( new_coords, "Destination: " );

  auto map_obj_src = getMapObjectShared( old_coords );
  auto map_obj_dest = getMapObjectShared( new_coords );

  err::passCondOrThrow<InvalidMapMoveException>( map_obj_src != nullptr,
                                                 "Tried moving object from an empty tile. Source coords:", old_coords );

  if ( map_obj_dest == nullptr ) {
    setMapObject( new_coords, map_obj_src );
    resetMapObject( old_coords );
    map_obj_src->setCoords( new_coords );
    return NoTransition{};
  }
  // TODO from here, below, battle is launched; rewrite cleanly

  bool is_dest_character = map_obj_dest->asCharacter() != nullptr;
  err::passCondOrThrow<InvalidMapMoveException>(
      is_dest_character, "Tried moving object onto an occupied tile. Destination coords:", new_coords );

  double distance = new_coords.distanceFrom( old_coords );
  err::passCondOrThrow<InvalidMapMoveException>( distance < 1.5,
                                                 "Tried engaging in battle from more than 1 tile away" );

  return RequestBattle{ .attacker_id_ = map_obj_src->asCharacter()->getId(),
                        .defender_id_ = map_obj_dest->asCharacter()->getId(),
                        .at_ = new_coords };
}
