#include <gtest/gtest.h>

#include <magic_enum/magic_enum.hpp>
#include <variant>

#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"

/*
====== Preset lookup tables ======
*/

// getUnitDataFromType() indexes the preset arrays by enum value, so every entry must sit at the index of its own type.
namespace {
template <typename UnitType>
class UnitPresetTest : public ::testing::Test {};
}  // namespace

using UnitTypes = ::testing::Types<CastleUnitType, RampartUnitType, TowerUnitType, InfernoUnitType, NecropolisUnitType,
                                   DungeonUnitType, StrongholdUnitType, FortressUnitType, ConfluxUnitType,
                                   ForgeUnitType, WarMachineType>;
TYPED_TEST_SUITE( UnitPresetTest, UnitTypes );

TYPED_TEST( UnitPresetTest, lookupReturnsDataOfRequestedType ) {
  for ( const TypeParam type : magic_enum::enum_values<TypeParam>() ) {
    SCOPED_TRACE( magic_enum::enum_name( type ) );

    const UnitData& data = getUnitDataFromType( type );

    ASSERT_TRUE( std::holds_alternative<TypeParam>( data.type_ ) );
    EXPECT_EQ( std::get<TypeParam>( data.type_ ), type );
  }
}

// All HoMM3 towns have real stats; Forge (not a HoMM3 town) is still a zero placeholder, so it is excluded.
namespace {
template <typename UnitType>
class TownUnitPresetTest : public ::testing::Test {};
}  // namespace

using TownUnitTypes =
    ::testing::Types<CastleUnitType, RampartUnitType, TowerUnitType, InfernoUnitType, NecropolisUnitType,
                     DungeonUnitType, StrongholdUnitType, FortressUnitType, ConfluxUnitType>;
TYPED_TEST_SUITE( TownUnitPresetTest, TownUnitTypes );

TYPED_TEST( TownUnitPresetTest, presetValuesAreSane ) {
  for ( const TypeParam type : magic_enum::enum_values<TypeParam>() ) {
    SCOPED_TRACE( magic_enum::enum_name( type ) );

    const UnitData& data = getUnitDataFromType( type );

    // town dwellings go from level 1 to 7 in enum order
    EXPECT_EQ( data.level_, static_cast<int>( type ) + 1 );
    EXPECT_GT( data.attack_, 0 );
    EXPECT_GT( data.defense_, 0 );
    EXPECT_GT( data.min_damage_, 0 );
    EXPECT_LE( data.min_damage_, data.max_damage_ );
    EXPECT_GT( data.health_, 0 );
    EXPECT_GT( data.speed_, 0 );
    EXPECT_GE( data.counter_attack_, 1 );
    EXPECT_GT( data.growth_, 0 );
    EXPECT_GT( data.cost_, 0 );
    EXPECT_GT( data.fight_value_, 0 );
  }
}

TEST( UnitPresetValuesTest, matchesHomm3Stats ) {
  const UnitData& pikeman = getUnitDataFromType( CastleUnitType::PIKEMAN );
  EXPECT_EQ( pikeman.attack_, 4 );
  EXPECT_EQ( pikeman.defense_, 5 );
  EXPECT_EQ( pikeman.speed_, 4 );
  EXPECT_EQ( pikeman.growth_, 14 );

  const UnitData& griffin = getUnitDataFromType( CastleUnitType::GRIFFIN );
  EXPECT_EQ( griffin.counter_attack_, 2 );

  const UnitData& lich = getUnitDataFromType( NecropolisUnitType::LICH );
  EXPECT_TRUE( lich.is_range_ );
  EXPECT_EQ( lich.min_damage_, 11 );
  EXPECT_EQ( lich.max_damage_, 13 );

  const UnitData& firebird = getUnitDataFromType( ConfluxUnitType::FIREBIRD );
  EXPECT_EQ( firebird.speed_, 15 );
  EXPECT_EQ( firebird.growth_, 2 );  // SoD value, HotA lowered it to 1

  const UnitData& ballista = getUnitDataFromType( WarMachineType::BALLISTA );
  EXPECT_TRUE( ballista.is_range_ );
  EXPECT_EQ( ballista.health_, 250 );
  EXPECT_EQ( ballista.counter_attack_, 0 );
}

/*
====== UnitStack ======
*/

TEST( UnitStackTest, constructedStackUsesPresetData ) {
  const UnitStack angels{ CastleUnitType::ANGEL, 5 };

  EXPECT_EQ( &angels.getData(), &getUnitDataFromType( CastleUnitType::ANGEL ) );
  EXPECT_EQ( angels.getSize(), 5 );
  EXPECT_TRUE( angels.isAlive() );
  EXPECT_EQ( angels.getMorale(), 0 );
  EXPECT_EQ( angels.getLuck(), 0 );
}

TEST( UnitStackTest, damageBelowOneUnitHealthKillsNoUnit ) {
  UnitStack pikemen{ CastleUnitType::PIKEMAN, 10 };
  const int unit_health = pikemen.getData().health_;
  ASSERT_GT( unit_health, 1 );

  pikemen.modifyCurrentHealth( unit_health - 1 );

  EXPECT_EQ( pikemen.getSize(), 10 );
  EXPECT_TRUE( pikemen.isAlive() );
}

TEST( UnitStackTest, damageEqualToOneUnitHealthKillsExactlyOneUnit ) {
  UnitStack pikemen{ CastleUnitType::PIKEMAN, 10 };
  const int unit_health = pikemen.getData().health_;

  pikemen.modifyCurrentHealth( unit_health );

  EXPECT_EQ( pikemen.getSize(), 9 );
  EXPECT_TRUE( pikemen.isAlive() );
}

TEST( UnitStackTest, partialDamageAccumulatesAcrossHits ) {
  UnitStack pikemen{ CastleUnitType::PIKEMAN, 10 };
  const int unit_health = pikemen.getData().health_;
  ASSERT_GT( unit_health, 1 );

  pikemen.modifyCurrentHealth( unit_health - 1 );
  pikemen.modifyCurrentHealth( 1 );

  EXPECT_EQ( pikemen.getSize(), 9 );
}

TEST( UnitStackTest, overkillDestroysWholeStack ) {
  UnitStack pikemen{ CastleUnitType::PIKEMAN, 10 };
  const int unit_health = pikemen.getData().health_;

  pikemen.modifyCurrentHealth( unit_health * 100 );

  EXPECT_EQ( pikemen.getSize(), 0 );
  EXPECT_FALSE( pikemen.isAlive() );
}

TEST( UnitStackTest, moraleAndLuckSetters ) {
  UnitStack pikemen{ CastleUnitType::PIKEMAN, 1 };

  pikemen.setMorale( 2 );
  pikemen.setLuck( -1 );

  EXPECT_EQ( pikemen.getMorale(), 2 );
  EXPECT_EQ( pikemen.getLuck(), -1 );
}
