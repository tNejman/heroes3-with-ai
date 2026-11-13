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

using UnitTypes = ::testing::Types<CastleUnitType, ConfluxUnitType, ForgeUnitType, WarMachineType>;
TYPED_TEST_SUITE( UnitPresetTest, UnitTypes );

TYPED_TEST( UnitPresetTest, lookupReturnsDataOfRequestedType ) {
  for ( const TypeParam type : magic_enum::enum_values<TypeParam>() ) {
    SCOPED_TRACE( magic_enum::enum_name( type ) );

    const UnitData& data = getUnitDataFromType( type );

    ASSERT_TRUE( std::holds_alternative<TypeParam>( data.type_ ) );
    EXPECT_EQ( std::get<TypeParam>( data.type_ ), type );
  }
}

// Only Castle has real stats so far; Forge, Conflux and war machine presets are still zero placeholders.
TEST( CastleUnitPresetTest, presetValuesAreSane ) {
  for ( const CastleUnitType type : magic_enum::enum_values<CastleUnitType>() ) {
    SCOPED_TRACE( magic_enum::enum_name( type ) );

    const UnitData& data = getUnitDataFromType( type );

    EXPECT_GT( data.health_, 0 );
    EXPECT_GE( data.min_damage_, 0 );
    EXPECT_LE( data.min_damage_, data.max_damage_ );
  }
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
