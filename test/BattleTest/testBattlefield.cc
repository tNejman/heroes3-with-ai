#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <memory>

#include "Battle/BattleField.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/GridTile.h"

TEST( LayoutTest, check_up_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF - 1; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[UR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[UR] ) );
    };
  }
  // top row
  const uint32_t max_y = MAP_HEIGHT_BF - 1;
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, max_y ) )[UR], nullptr );
  }
  // right column
  const uint32_t max_x = MAP_WIDTH_BF - 1;
  for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[UR], nullptr );
  }
}  // done

TEST( LayoutTest, check_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++y ) {
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[R],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[R] ) );
    }
  }
  // right column
  const uint32_t max_x = MAP_WIDTH_BF - 1;
  for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[R], nullptr );
  }
}  // done

TEST( LayoutTest, check_down_right_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 2; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[DR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[DR] ) );
    }
  }
  // max right col
  const uint32_t max_x = MAP_WIDTH_BF - 1;
  for ( uint32_t y = 2; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[DR], nullptr );
  }
  // max bottom row
  const uint32_t min_y = 0u;
  for ( uint32_t x = 0; x < MAP_WIDTH_BF - 1; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, min_y ) )[DR], nullptr );
  }
}  // done

TEST( LayoutTest, check_down_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 2; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[DL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[DL] ) );
    }
  }
  // max bottom row
  const uint32_t min_y = 0u;
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, min_y ) )[DL], nullptr );
  }
}  // done

TEST( LayoutTest, check_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 1; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[L],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[L] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 0; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[L], nullptr );
  }
}  // done

TEST( LayoutTest, check_up_left_neighbour_even ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 0; y < MAP_HEIGHT_BF - 1; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[UL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + EVEN_DIRECTIONS_BATTLE[UL] ) );
    }
  }
  const uint32_t max_y = MAP_HEIGHT_BF - 1;
  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, max_y ) )[UL], nullptr );
  }
}  // done

TEST( LayoutTest, check_up_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[UR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[UR] ) );
    }
  }
}  // done

TEST( LayoutTest, check_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < MAP_WIDTH_BF - 1; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[R],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[R] ) );
    }
  }
  const uint32_t max_x = MAP_WIDTH_BF - 1;
  for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( max_x, y ) )[R], nullptr );
  }
}  // done

TEST( LayoutTest, check_down_right_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[DR],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[DR] ) );
    }
  }
}  // done

TEST( LayoutTest, check_down_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[DL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[DL] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[DL], nullptr );
  }
}  // done

TEST( LayoutTest, check_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[L],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[L] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[L], nullptr );
  }
}  // done

TEST( LayoutTest, check_up_left_neighbour_odd ) {
  std::shared_ptr<GridTile> grid_tile = std::make_shared<GridTile>( CoordPair{ 0, 0 }, Terrain::GRASS );
  std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>( grid_tile );

  for ( uint32_t x = 1; x < MAP_WIDTH_BF; ++x ) {
    for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
      if ( y >= MAP_HEIGHT_BF ) continue;
      ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( x, y ) )[UL],
                 battlefield->getTileByProxy( CoordPair( x, y ) + ODD_DIRECTIONS_BATTLE[UL] ) );
    }
  }
  const uint32_t min_x = 0u;
  for ( uint32_t y = 1; y < MAP_HEIGHT_BF; ++ ++y ) {
    if ( y >= MAP_HEIGHT_BF ) continue;
    ASSERT_EQ( battlefield->getTileNeighbours( CoordPair( min_x, y ) )[UL], nullptr );
  }
}

// WIP
// TEST( LayoutConnection, checkingIfConnected ) {
//   std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>();
//   ASSERT_EQ(2,battlefield->ifConnected(0,0,2,1));
// }

// TEST( LayoutConnection, checkingIfConnectedfar ) {
//   std::unique_ptr<BattleField> battlefield = std::make_unique<BattleField>();
//   ASSERT_EQ(19,battlefield->ifConnected(0,0,14,10));
// }