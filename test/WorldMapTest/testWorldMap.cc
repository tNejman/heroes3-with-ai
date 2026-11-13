#include <gtest/gtest.h>

#include <memory>
#include <ranges>
#include <variant>
#include <vector>

#include "core/Exceptions/CoordinateOutOfBoundsException.hpp"
#include "core/Exceptions/InvalidMapMoveException.hpp"
#include "core/Game/IState.h"
#include "core/Misc/ProjectLib.h"
#include "core/WorldMap/OverworldObstacle.h"
#include "core/WorldMap/WorldMap.h"
#include "engine/model/IGame/Coords.h"

namespace {

constexpr int DIRT = static_cast<int>( Terrain::DIRT );

WorldMapGrid<int> filledGrid( int terrain ) {
  WorldMapGrid<int> grid{};
  for ( auto& column : grid ) {
    column.fill( terrain );
  }
  return grid;
}

auto allCoords() {
  return std::views::cartesian_product( std::views::iota( 0, WORLD_MAP_WIDTH ),
                                        std::views::iota( 0, WORLD_MAP_HEIGHT ) )
         | std::views::transform( []( auto xy ) { return CoordPair{ std::get<0>( xy ), std::get<1>( xy ) }; } );
}

std::shared_ptr<OverworldObstacle> makeTree( CoordPair coords ) {
  return std::make_shared<OverworldObstacle>( OverworldObstacleType::DRIED_TREE, coords );
}

class WorldMapTest : public ::testing::Test {
 protected:
  const WorldMapGrid<int> grid_ = filledGrid( DIRT );
  WorldMap world_map_{ grid_ };
};

}  // namespace

/*
====== Loading ======
*/

TEST_F( WorldMapTest, loadGridSetsTerrainAndLeavesForegroundEmpty ) {
  for ( const CoordPair coords : allCoords() ) {
    SCOPED_TRACE( coords );
    ASSERT_EQ( world_map_.getTerrain( coords ), Terrain::DIRT );
    ASSERT_EQ( world_map_.getMapObject( coords ), nullptr );
  }
}

TEST_F( WorldMapTest, loadObstaclesPlacesThemAtTheirCoords ) {
  const std::vector obstacles{
      std::make_shared<OverworldObstacle>( OverworldObstacleType::DRIED_TREE, CoordPair( 1, 1 ) ),
      std::make_shared<OverworldObstacle>( OverworldObstacleType::GREEN_TREE, CoordPair( 2, 2 ) ),
  };

  const auto world_map = std::make_unique<WorldMap>( grid_, obstacles );

  EXPECT_EQ( world_map->getMapObject( { 1, 1 } ), obstacles[0].get() );
  EXPECT_EQ( world_map->getMapObject( { 2, 2 } ), obstacles[1].get() );
}

TEST_F( WorldMapTest, loadObstaclesOnSameTileKeepsTheLastOne ) {
  const std::vector obstacles{
      std::make_shared<OverworldObstacle>( OverworldObstacleType::DRIED_TREE, CoordPair( 1, 1 ) ),
      std::make_shared<OverworldObstacle>( OverworldObstacleType::GREEN_TREE, CoordPair( 1, 1 ) ),
  };

  const auto world_map = std::make_unique<WorldMap>( grid_, obstacles );

  EXPECT_EQ( world_map->getMapObject( { 1, 1 } ), obstacles[1].get() );
  for ( const CoordPair coords : allCoords() ) {
    SCOPED_TRACE( coords );
    ASSERT_NE( world_map->getMapObject( coords ), obstacles[0].get() );
  }
}

/*
====== Bounds ======
*/

TEST( WorldMapBoundsTest, areCoordsInBounds ) {
  EXPECT_TRUE( WorldMap::areCoordsInBounds( { 0, 0 } ) );
  EXPECT_TRUE( WorldMap::areCoordsInBounds( { WORLD_MAP_WIDTH - 1, WORLD_MAP_HEIGHT - 1 } ) );

  EXPECT_FALSE( WorldMap::areCoordsInBounds( { -1, 0 } ) );
  EXPECT_FALSE( WorldMap::areCoordsInBounds( { 0, -1 } ) );
  EXPECT_FALSE( WorldMap::areCoordsInBounds( { WORLD_MAP_WIDTH, 0 } ) );
  EXPECT_FALSE( WorldMap::areCoordsInBounds( { 0, WORLD_MAP_HEIGHT } ) );
}

/*
====== Setting ======
*/

TEST_F( WorldMapTest, setMapObject ) {
  const auto obstacle = makeTree( { 1, 1 } );

  world_map_.setMapObject( { 1, 1 }, obstacle );

  EXPECT_EQ( world_map_.getMapObject( { 1, 1 } ), obstacle.get() );
}

TEST_F( WorldMapTest, setMapObjectOnOccupiedTileReplacesIt ) {
  const auto obstacle1 = makeTree( { 1, 1 } );
  const auto obstacle2 = makeTree( { 1, 1 } );

  world_map_.setMapObject( { 1, 1 }, obstacle1 );
  world_map_.setMapObject( { 1, 1 }, obstacle2 );

  EXPECT_EQ( world_map_.getMapObject( { 1, 1 } ), obstacle2.get() );
}

TEST_F( WorldMapTest, resetMapObjectEmptiesTile ) {
  world_map_.setMapObject( { 1, 1 }, makeTree( { 1, 1 } ) );

  world_map_.resetMapObject( { 1, 1 } );

  EXPECT_EQ( world_map_.getMapObject( { 1, 1 } ), nullptr );
}

/*
====== Moving ======
*/

TEST_F( WorldMapTest, moveMapObject ) {
  const auto obstacle = makeTree( { 1, 1 } );
  world_map_.setMapObject( { 1, 1 }, obstacle );

  const game::StateTransition transition = world_map_.moveMapObject( { 1, 1 }, { 2, 2 } );

  EXPECT_TRUE( std::holds_alternative<game::NoTransition>( transition ) );
  EXPECT_EQ( world_map_.getMapObject( { 2, 2 } ), obstacle.get() );
  EXPECT_EQ( world_map_.getMapObject( { 1, 1 } ), nullptr );
  EXPECT_EQ( obstacle->getCoords(), CoordPair( 2, 2 ) );
}

TEST_F( WorldMapTest, moveMapObjectOutOfBoundsThrows ) {
  world_map_.setMapObject( { 1, 1 }, makeTree( { 1, 1 } ) );

  EXPECT_THROW( (void)world_map_.moveMapObject( { 1, 1 }, { WORLD_MAP_WIDTH + 10, WORLD_MAP_HEIGHT + 10 } ),
                CoordinateOutOfBoundsException );
  EXPECT_THROW( (void)world_map_.moveMapObject( { -1, 0 }, { 1, 1 } ), CoordinateOutOfBoundsException );
}

TEST_F( WorldMapTest, moveMapObjectOntoOccupiedTileThrows ) {
  world_map_.setMapObject( { 1, 1 }, makeTree( { 1, 1 } ) );
  world_map_.setMapObject( { 2, 2 }, makeTree( { 2, 2 } ) );

  EXPECT_THROW( (void)world_map_.moveMapObject( { 1, 1 }, { 2, 2 } ), InvalidMapMoveException );
}

TEST_F( WorldMapTest, moveMapObjectFromEmptyTileThrows ) {
  EXPECT_THROW( (void)world_map_.moveMapObject( { 1, 1 }, { 2, 2 } ), InvalidMapMoveException );
}
