#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Exceptions/InvalidMapMoveException.hpp"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

TEST( WorldMapTests, constructorWithGrid ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }
  for ( uint32_t i = 0; i < WORLD_MAP_WIDTH; ++i ) {
    for ( uint32_t j = 0; j < WORLD_MAP_HEIGHT; ++j ) {
      if ( i % 2 && j % 2 ) {
        grid_temp[i][j] = 0;
      }
    }
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );
  for ( auto x = 0u; x < WORLD_MAP_WIDTH; ++x ) {
    for ( auto y = 0u; y < WORLD_MAP_HEIGHT; ++y ) {
      ASSERT_NO_THROW( world_map->getTile( CoordPair( x, y ) ) );
    }
  }
}

TEST( WorldMapTests, loadGrid ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }
  std::shared_ptr<WorldMap> world_map = nullptr;
  ASSERT_NO_THROW( world_map = std::make_shared<WorldMap>( grid_temp ) );
  for ( auto x = 0u; x < WORLD_MAP_WIDTH; ++x ) {
    for ( auto y = 0u; y < WORLD_MAP_HEIGHT; ++y ) {
      ASSERT_NO_THROW( world_map->getTile( CoordPair( x, y ) ) );
    }
  }
}

TEST( WorldMapTests, loadObstacles ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  std::vector<std::shared_ptr<OverworldObstacle>> obstacles;
  obstacles.push_back( std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) ) );
  obstacles.push_back( std::make_shared<OverworldObstacle>( "Obstacle2", CoordPair( 2, 2 ) ) );

  ASSERT_NO_THROW( world_map->loadObstacles( obstacles ) );
  ASSERT_NO_THROW( world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
  ASSERT_NO_THROW( world_map->getTile( CoordPair( 2, 2 ) )->getMapObject() );

  ASSERT_EQ( obstacles[0], world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
  ASSERT_EQ( obstacles[1], world_map->getTile( CoordPair( 2, 2 ) )->getMapObject() );
}

TEST( WorldMapTests, loadObjectsDuplicated ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  std::vector<std::shared_ptr<OverworldObstacle>> obstacles;
  obstacles.push_back( std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) ) );
  obstacles.push_back( std::make_shared<OverworldObstacle>( "Obstacle2", CoordPair( 1, 1 ) ) );

  ASSERT_NO_THROW( world_map->loadObstacles( obstacles ) );
  ASSERT_NO_THROW( world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );

  // check if the first obstacle was replaced by the second one
  for ( auto x = 0u; x < WORLD_MAP_WIDTH; ++x ) {
    for ( auto y = 0u; y < WORLD_MAP_HEIGHT; ++y ) {
      ASSERT_NE( world_map->getTile( CoordPair( x, y ) )->getMapObject(), obstacles[0] );
    }
  }
  ASSERT_EQ( obstacles[1], world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
}

TEST( WorldMapTests, setMapObject ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) );
  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle ) );

  ASSERT_EQ( obstacle, world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
}

TEST( WorldMapTests, setMapObjectOutOfBounds ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( WORLD_MAP_WIDTH, WORLD_MAP_HEIGHT ) );
  ASSERT_THROW( world_map->setMapObject( CoordPair( WORLD_MAP_WIDTH, WORLD_MAP_HEIGHT ), obstacle ),
                CoordinateOutOfBoundsException );
}

TEST( WorldMapTests, setMapObjectOnOccupiedTile ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle1 = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) );
  auto obstacle2 = std::make_shared<OverworldObstacle>( "Obstacle2", CoordPair( 1, 1 ) );

  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle1 ) );
  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle2 ) );
  ASSERT_NE( obstacle1, world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
  ASSERT_EQ( obstacle2, world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
}

TEST( WorldMapTests, moveMapObject ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) );
  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle ) );

  ASSERT_NO_THROW( world_map->moveMapObject( CoordPair( 1, 1 ), CoordPair( 2, 2 ) ) );
  ASSERT_EQ( obstacle, world_map->getTile( CoordPair( 2, 2 ) )->getMapObject() );
  ASSERT_EQ( nullptr, world_map->getTile( CoordPair( 1, 1 ) )->getMapObject() );
}

TEST( WorldMapTests, moveMapObjectOutOfBounds ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) );
  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle ) );

  ASSERT_THROW( world_map->moveMapObject( CoordPair( 1, 1 ), CoordPair( WORLD_MAP_WIDTH + 10, WORLD_MAP_HEIGHT + 10 ) ),
                CoordinateOutOfBoundsException );
}

TEST( WorldMapTests, moveMapObjectOnOccupiedTile ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  auto obstacle1 = std::make_shared<OverworldObstacle>( "Obstacle1", CoordPair( 1, 1 ) );
  auto obstacle2 = std::make_shared<OverworldObstacle>( "Obstacle2", CoordPair( 2, 2 ) );

  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 1, 1 ), obstacle1 ) );
  ASSERT_NO_THROW( world_map->setMapObject( CoordPair( 2, 2 ), obstacle2 ) );

  ASSERT_THROW( world_map->moveMapObject( CoordPair( 1, 1 ), CoordPair( 2, 2 ) ), InvalidMapMoveException );
}

TEST( WorldMapTests, moveMapObjectNoExisting ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  ASSERT_THROW( world_map->moveMapObject( CoordPair( 1, 1 ), CoordPair( 2, 2 ) ), InvalidMapMoveException );
}

TEST( WorldMapTests, getTile ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  ASSERT_NO_THROW( world_map->getTile( CoordPair( 0, 0 ) ) );
  ASSERT_NO_THROW( world_map->getTile( CoordPair( WORLD_MAP_WIDTH - 1, WORLD_MAP_HEIGHT - 1 ) ) );
}

TEST( WorldMapTests, getTileOutOfBounds ) {
  std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH> grid_temp{};
  for ( auto& col : grid_temp ) {
    col.fill( 1 );
  }

  std::shared_ptr<WorldMap> world_map = std::make_shared<WorldMap>( grid_temp );

  ASSERT_THROW( world_map->getTile( CoordPair( WORLD_MAP_WIDTH + 1, WORLD_MAP_HEIGHT + 1 ) ),
                CoordinateOutOfBoundsException );
}