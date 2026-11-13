#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

#include "core/Battle/BattleField.h"
#include "core/Battle/Tile.h"  // IWYU pragma: keep (Tile::getCoords)
#include "core/Exceptions/CoordinateOutOfBoundsException.hpp"
#include "core/Misc/ProjectLib.h"
#include "engine/model/IGame/Coords.h"

namespace {

bool isOnBattlefield( CoordPair coords ) {
  return coords.x_ >= 0 && coords.x_ < MAP_WIDTH_BF && coords.y_ >= 0 && coords.y_ < MAP_HEIGHT_BF;
}

auto allBattlefieldCoords() {
  return std::views::cartesian_product( std::views::iota( 0, MAP_WIDTH_BF ), std::views::iota( 0, MAP_HEIGHT_BF ) )
         | std::views::transform( []( auto xy ) { return CoordPair{ std::get<0>( xy ), std::get<1>( xy ) }; } );
}

// Coordinates of each neighbour in BATTLE_DIRECTIONS order; std::nullopt where the neighbour is off the battlefield.
using Neighbourhood = std::array<std::optional<CoordPair>, 6>;

Neighbourhood neighbourCoords( BattleField& battlefield, CoordPair coords ) {
  const auto neighbours = battlefield.getTileNeighbours( coords );
  Neighbourhood result{};
  for ( auto [i, tile] : std::views::enumerate( neighbours ) | std::views::take( result.size() ) ) {
    if ( tile != nullptr ) {
      result.at( static_cast<std::size_t>( i ) ) = tile->getCoords();
    }
  }
  return result;
}

class BattleFieldTest : public ::testing::Test {
 protected:
  BattleField battlefield_{ Terrain::GRASS };
};

class BattleFieldNeighbourTest : public ::testing::TestWithParam<BATTLE_DIRECTIONS> {
 protected:
  BattleField battlefield_{ Terrain::GRASS };
};

}  // namespace

TEST_F( BattleFieldTest, everyTileHasSixNeighbourSlots ) {
  for ( const CoordPair coords : allBattlefieldCoords() ) {
    SCOPED_TRACE( coords );
    ASSERT_EQ( battlefield_.getTileNeighbours( coords ).size(), 6 );
  }
}

// Even rows are shifted right relative to odd rows, so the same direction maps to different shifts per row parity.
TEST_P( BattleFieldNeighbourTest, neighbourMatchesRowParityShiftOrIsNullOffTheMap ) {
  const auto direction = static_cast<std::size_t>( GetParam() );

  for ( const CoordPair coords : allBattlefieldCoords() ) {
    SCOPED_TRACE( coords );
    const auto& shifts = ( coords.y_ % 2 == 0 ) ? EVEN_DIRECTIONS_BATTLE : ODD_DIRECTIONS_BATTLE;
    const CoordPair expected = coords + shifts.at( direction );

    const auto neighbour = battlefield_.getTileNeighbours( coords ).at( direction );

    if ( isOnBattlefield( expected ) ) {
      ASSERT_EQ( neighbour, battlefield_.getTileByProxy( expected ) );
    } else {
      ASSERT_EQ( neighbour, nullptr );
    }
  }
}

INSTANTIATE_TEST_SUITE_P( AllDirections, BattleFieldNeighbourTest,
                          ::testing::ValuesIn( magic_enum::enum_values<BATTLE_DIRECTIONS>() ),
                          []( const ::testing::TestParamInfo<BATTLE_DIRECTIONS>& param_info ) {
                            return std::string( magic_enum::enum_name( param_info.param ) );
                          } );

// Hand-written expectations, independent of the EVEN/ODD lookup tables used by the implementation.
TEST_F( BattleFieldTest, neighboursOfEvenRowTile ) {
  const Neighbourhood expected{ CoordPair{ 8, 5 }, CoordPair{ 8, 4 }, CoordPair{ 8, 3 },
                                CoordPair{ 7, 3 }, CoordPair{ 6, 4 }, CoordPair{ 7, 5 } };

  EXPECT_EQ( neighbourCoords( battlefield_, { 7, 4 } ), expected );
}

TEST_F( BattleFieldTest, neighboursOfOddRowTile ) {
  const Neighbourhood expected{ CoordPair{ 7, 6 }, CoordPair{ 8, 5 }, CoordPair{ 7, 4 },
                                CoordPair{ 6, 4 }, CoordPair{ 6, 5 }, CoordPair{ 6, 6 } };

  EXPECT_EQ( neighbourCoords( battlefield_, { 7, 5 } ), expected );
}

TEST_F( BattleFieldTest, neighboursOfBottomLeftCorner ) {
  const Neighbourhood expected{ CoordPair{ 1, 1 }, CoordPair{ 1, 0 }, std::nullopt,
                                std::nullopt,      std::nullopt,      CoordPair{ 0, 1 } };

  EXPECT_EQ( neighbourCoords( battlefield_, { 0, 0 } ), expected );
}

TEST_F( BattleFieldTest, neighboursOfTopRightCorner ) {
  // top row (y = 10) is even, so it is shifted right and has no UR/R/UL neighbours at the right edge
  const Neighbourhood expected{ std::nullopt,       std::nullopt,        std::nullopt,
                                CoordPair{ 14, 9 }, CoordPair{ 13, 10 }, std::nullopt };

  EXPECT_EQ( neighbourCoords( battlefield_, BATTLE_MAP_TOP_RIGHT_COORDS ), expected );
}

TEST_F( BattleFieldTest, getTileByProxyOutsideBattlefieldThrows ) {
  EXPECT_THROW( battlefield_.getTileByProxy( { MAP_WIDTH_BF, 0 } ), CoordinateOutOfBoundsException );
  EXPECT_THROW( battlefield_.getTileByProxy( { 0, MAP_HEIGHT_BF } ), CoordinateOutOfBoundsException );
  EXPECT_THROW( battlefield_.getTileByProxy( { -1, 0 } ), CoordinateOutOfBoundsException );
}
