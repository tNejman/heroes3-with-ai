#include <gtest/gtest.h>

#include <memory>

#include "aux/Builder.hpp"
#include "core/Battle/Battle.h"
#include "core/Battle/Tile.h"  // IWYU pragma: keep
#include "core/Character/Character.h"
#include "core/Character/Stats.h"
#include "core/Misc/BuilderDefaults.hpp"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"
#include "core/Unit/UnitsLib.h"
#include "engine/model/IGame/Coords.h"

namespace {

struct HeroSkills {
  int attack_ = 0;
  int defense_ = 0;
};

std::shared_ptr<Character> makeHero( HeroSkills skills = {} ) {
  return Builder<Character>{}
      .setStats( Builder<character::Stats>{}
                     .setPrimarySkills( character::Stats::PrimarySkills{
                         .attack_ = skills.attack_, .defense_ = skills.defense_, .power_ = 10, .knowledge_ = 10 } )
                     .build() )
      .build<std::shared_ptr>();
}

const TileObject* objectAt( Battle& battle, CoordPair coords ) {
  return battle.getBattlefield()->getTileByProxy( coords )->getObject();
}

// Three pikemen stacks (attacker) vs. an angel and three swordsmen stacks (defender) on grass.
class BattleWithArmiesTest : public ::testing::Test {
 protected:
  std::shared_ptr<Character> attacker_ = makeHero();
  std::shared_ptr<Character> defender_ = makeHero();

  UnitStack& pikemen_1_ = attacker_->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  UnitStack& pikemen_2_ = attacker_->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  UnitStack& pikemen_3_ = attacker_->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );

  UnitStack& angels_ = defender_->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );
  UnitStack& swordsmen_1_ = defender_->army().recruitUnitStack( UnitStack{ CastleUnitType::SWORDSMAN, 2 } );
  UnitStack& swordsmen_2_ = defender_->army().recruitUnitStack( UnitStack{ CastleUnitType::SWORDSMAN, 3 } );
  UnitStack& swordsmen_3_ = defender_->army().recruitUnitStack( UnitStack{ CastleUnitType::SWORDSMAN, 4 } );

  Battle battle_{ attacker_, defender_, Terrain::GRASS };
};

}  // namespace

/*
====== Damage ======
Note: Battle::attack() takes the hero bonus from the battle's attacker/defender heroes, regardless of which side's
stack is attacking.
*/

TEST( BattleTest, angelSurvivesPikemenAndDamagesThemBack ) {
  const auto attacker = makeHero();
  const auto defender = makeHero();
  auto& pikemen = attacker->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  auto& angel = defender->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );
  Battle battle{ attacker, defender, Terrain::GRASS };

  battle.attack( pikemen, angel );
  EXPECT_EQ( angel.getSize(), 1 );

  battle.attack( angel, pikemen );
  EXPECT_LT( pikemen.getSize(), 30 );
}

TEST( BattleTest, higherHeroAttackDealsMoreDamage ) {
  const auto weak_attacker = makeHero( { .attack_ = 10, .defense_ = 10 } );
  const auto strong_attacker = makeHero( { .attack_ = 100, .defense_ = 100 } );
  const auto defender_1 = makeHero();
  const auto defender_2 = makeHero();

  auto& weak_side_pikemen = weak_attacker->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  auto& strong_side_pikemen = defender_2->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  auto& angel_1 = defender_1->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );
  auto& angel_2 = strong_attacker->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );

  Battle weak_battle{ weak_attacker, defender_1, Terrain::GRASS };
  Battle strong_battle{ strong_attacker, defender_2, Terrain::GRASS };

  weak_battle.attack( angel_1, weak_side_pikemen );
  strong_battle.attack( angel_2, strong_side_pikemen );

  EXPECT_LT( weak_side_pikemen.getSize(), 30 );
  EXPECT_LT( strong_side_pikemen.getSize(), 30 );
  EXPECT_GT( weak_side_pikemen.getHealthPool(), strong_side_pikemen.getHealthPool() );
}

TEST( BattleTest, attackBonusIsCapped ) {
  // both attack advantages are far above the cap, so both hits must deal identical damage
  const auto attacker_4000 = makeHero( { .attack_ = 4000, .defense_ = 4000 } );
  const auto attacker_100 = makeHero( { .attack_ = 100, .defense_ = 100 } );
  const auto defender_1 = makeHero();
  const auto defender_2 = makeHero();

  auto& pikemen_1 = attacker_4000->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  auto& pikemen_2 = defender_2->army().recruitUnitStack( UnitStack{ CastleUnitType::PIKEMAN, 30 } );
  auto& angel_1 = defender_1->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );
  auto& angel_2 = attacker_100->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 1 } );

  Battle battle_1{ attacker_4000, defender_1, Terrain::GRASS };
  Battle battle_2{ attacker_100, defender_2, Terrain::GRASS };

  battle_1.attack( angel_1, pikemen_1 );
  battle_2.attack( angel_2, pikemen_2 );

  EXPECT_LT( pikemen_1.getSize(), 30 );
  EXPECT_LT( pikemen_2.getSize(), 30 );
  EXPECT_EQ( pikemen_1.getHealthPool(), pikemen_2.getHealthPool() );
}

TEST( BattleTest, killedStackIsRemovedFromParty ) {
  const auto attacker_200 = makeHero( { .attack_ = 200, .defense_ = 200 } );
  const auto attacker_100 = makeHero( { .attack_ = 100, .defense_ = 100 } );
  const auto defender_1 = makeHero();
  const auto defender_2 = makeHero();

  auto& angels_1 = attacker_200->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 5 } );
  auto& angels_2 = defender_1->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 5 } );
  auto& angels_3 = attacker_100->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 5 } );
  auto& angels_4 = defender_2->army().recruitUnitStack( UnitStack{ CastleUnitType::ANGEL, 5 } );

  Battle battle_1{ attacker_200, defender_1, Terrain::GRASS };
  Battle battle_2{ attacker_100, defender_2, Terrain::GRASS };

  ASSERT_TRUE( attacker_200->army().getParty()[0].has_value() );
  ASSERT_TRUE( attacker_100->army().getParty()[0].has_value() );

  battle_1.attack( angels_2, angels_1 );
  battle_2.attack( angels_4, angels_3 );

  EXPECT_FALSE( attacker_200->army().getParty()[0].has_value() );
  EXPECT_FALSE( attacker_100->army().getParty()[0].has_value() );
}

/*
====== Deployment & movement ======
*/

TEST_F( BattleWithArmiesTest, armiesAreDeployedOnOppositeEdges ) {
  EXPECT_EQ( objectAt( battle_, { 0, 0 } ), &pikemen_1_ );
  EXPECT_EQ( objectAt( battle_, { 0, 2 } ), &pikemen_2_ );
  EXPECT_EQ( objectAt( battle_, { 0, 4 } ), &pikemen_3_ );

  EXPECT_EQ( objectAt( battle_, { 14, 0 } ), &angels_ );
  EXPECT_EQ( objectAt( battle_, { 14, 2 } ), &swordsmen_1_ );
  EXPECT_EQ( objectAt( battle_, { 14, 4 } ), &swordsmen_2_ );
  EXPECT_EQ( objectAt( battle_, { 14, 5 } ), &swordsmen_3_ );
}

TEST_F( BattleWithArmiesTest, moveRelocatesUnit ) {
  ASSERT_EQ( objectAt( battle_, { 14, 0 } ), &angels_ );

  battle_.move( angels_, { 0, 9 } );

  EXPECT_EQ( objectAt( battle_, { 0, 9 } ), &angels_ );
}

TEST_F( BattleWithArmiesTest, attackDamagesAdjacentDefenderWithoutHurtingAttacker ) {
  battle_.move( pikemen_1_, { 7, 5 } );
  battle_.move( swordsmen_1_, { 7, 6 } );

  battle_.attack( pikemen_1_, swordsmen_1_ );

  EXPECT_LT( swordsmen_1_.getSize(), 2 );
  EXPECT_EQ( pikemen_1_.getSize(), 30 );
}
