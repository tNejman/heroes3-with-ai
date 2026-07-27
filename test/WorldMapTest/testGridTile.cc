#include <gtest/gtest.h>

#include <memory>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/Building.h"
#include "WorldMap/GridTile.h"

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

TEST( GridTileTest, construtor1 ) {
  GridTile grid_tile{ { .x_ = 0, .y_ = 0 }, Terrain::DIRT };
  ASSERT_EQ( grid_tile.getCoords(), ( CoordPair{ 0U, 0U } ) );
  ASSERT_EQ( grid_tile.getTerrain(), Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
}

TEST( GridTileTest, constructor2 ) {
  GridTile grid_tile{ { .x_ = 15U, .y_ = 3U }, Terrain::DIRT };
  ASSERT_EQ( grid_tile.getCoords(), ( CoordPair{ 15U, 3U } ) );
  ASSERT_EQ( grid_tile.getTerrain(), Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
}

TEST( GridTileTest, constructor3 ) {
  auto building = std::make_shared<Building>( CoordPair{ .x_ = 17U, .y_ = 29U }, "" );
  GridTile grid_tile{ CoordPair{ .x_ = 15U, .y_ = 3U }, Terrain::DIRT, building };
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 15U, 3U ) );
  ASSERT_EQ( grid_tile.getTerrain(), Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), building );
}

TEST( GridTileTest, objectPresentModifications ) {
  GridTile grid_tile{ CoordPair( 15U, 3U ), Terrain::DIRT };
  ASSERT_EQ( grid_tile.getCoords(), CoordPair( 15U, 3U ) );
  ASSERT_EQ( grid_tile.getTerrain(), Terrain::DIRT );
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );

  auto building = std::make_shared<Building>( CoordPair( 17U, 29U ), "" );
  grid_tile.setMapObject( building );
  ASSERT_EQ( grid_tile.getMapObject(), building );
  ASSERT_FALSE( grid_tile.isTraversable() );

  grid_tile.deleteObject();
  ASSERT_EQ( grid_tile.getMapObject(), nullptr );
  ASSERT_TRUE( grid_tile.isTraversable() );
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)