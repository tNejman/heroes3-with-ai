#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include "Battle/Battle.h"
#include "Battle/Tile.h"
#include "Character/Character.h"
#include "Character/CharacterBuilder.h"
#include "Character/CharacterStats.h"
#include "Miscellaneous/Coords.h"
#include "Unit/Faction.hpp"
#include "Unit/Unit.h"
#include "Unit/UnitsLib.h"

// Easy factory constructor
// const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
// std::shared_ptr<const Unit> pikeman = faction_castle->getUnit(CastleUnitType::PIKEMAN);
// std::shared_ptr<const Unit> archer = faction_castle->getUnit(CastleUnitType::ARCHER);
// std::shared_ptr<const Unit> griffin = faction_castle->getUnit(CastleUnitType::GRIFFIN);
// std::shared_ptr<const Unit> swordsman = faction_castle->getUnit(CastleUnitType::SWORDSMAN);
// std::shared_ptr<const Unit> monk = faction_castle->getUnit(CastleUnitType::MONK);
// std::shared_ptr<const Unit> cavalier = faction_castle->getUnit(CastleUnitType::CAVALIER);
// std::shared_ptr<const Unit> angel = faction_castle->getUnit(CastleUnitType::ANGEL);

TEST( BattleTest, checkattacking ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );
  std::shared_ptr<UnitStack> pikeman_army = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> angel_army = std::make_shared<UnitStack>( angel, (uint32_t)1 );

  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army );
  character2->army().recruitUnitStack( angel_army );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  battle->attack( pikeman_army, angel_army );
  ASSERT_EQ( angel_army->getSize(), 1 );
  battle->attack( angel_army, pikeman_army );
  ASSERT_TRUE( pikeman_army->getSize() < 30 );
}

TEST( BattleTest, checkingattacking ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );

  std::shared_ptr<UnitStack> pikeman_army_john = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> pikeman_army_panam = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> angel_army_silverhand = std::make_shared<UnitStack>( angel, (uint32_t)1 );
  std::shared_ptr<UnitStack> angel_army_v = std::make_shared<UnitStack>( angel, (uint32_t)1 );

  std::shared_ptr<Character> character1 =
      CharacterBuilder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character2 =
      CharacterBuilder{}
          .setName( "Silverhand" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character3 =
      CharacterBuilder{}
          .setName( "V" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 100, .defense_ = 100, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character4 =
      CharacterBuilder{}
          .setName( "Panam" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army_john );
  character2->army().recruitUnitStack( angel_army_silverhand );
  character3->army().recruitUnitStack( angel_army_v );
  character4->army().recruitUnitStack( pikeman_army_panam );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  std::unique_ptr<Battle> battle_v_panam = std::make_unique<Battle>( character3, character4, tile );

  battle->attack( pikeman_army_john, angel_army_silverhand );
  ASSERT_EQ( angel_army_silverhand->getSize(), 1 );
  battle->attack( angel_army_silverhand, pikeman_army_john );
  ASSERT_TRUE( pikeman_army_john->getSize() < 30 );
  battle_v_panam->attack( angel_army_v, pikeman_army_panam );
  ASSERT_TRUE( pikeman_army_john->getHealthPool() > pikeman_army_panam->getHealthPool() );
}

TEST( BattleTest, checkingMaxattackBonus ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );

  std::shared_ptr<UnitStack> pikeman_army_john = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> pikeman_army_panam = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> angel_army_silverhand = std::make_shared<UnitStack>( angel, (uint32_t)1 );
  std::shared_ptr<UnitStack> angel_army_v = std::make_shared<UnitStack>( angel, (uint32_t)1 );

  std::shared_ptr<Character> character1 =
      CharacterBuilder{}
          .setName( "John" )
          .setCoords( { 0, 0 } )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 4000, .defense_ = 4000, .power_ = 10, .knowledge_ = 10 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character3 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 100, .defense_ = 100, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character4 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army_john );
  character2->army().recruitUnitStack( angel_army_silverhand );
  character3->army().recruitUnitStack( angel_army_v );
  character4->army().recruitUnitStack( pikeman_army_panam );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  std::unique_ptr<Battle> battle_v_panam = std::make_unique<Battle>( character3, character4, tile );

  battle->attack( angel_army_silverhand, pikeman_army_john );
  ASSERT_TRUE( pikeman_army_john->getSize() < 30 );
  battle_v_panam->attack( angel_army_v, pikeman_army_panam );
  ASSERT_TRUE( pikeman_army_panam->getSize() < 30 );
  ASSERT_EQ( pikeman_army_john->getHealthPool(), pikeman_army_panam->getHealthPool() );
}

TEST( BattleTest, checkingMaxdefenseBonus ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );

  std::shared_ptr<UnitStack> angel_army_john = std::make_shared<UnitStack>( angel, (uint32_t)5 );
  std::shared_ptr<UnitStack> angel_army_panam = std::make_shared<UnitStack>( angel, (uint32_t)5 );
  std::shared_ptr<UnitStack> angel_army_silverhand = std::make_shared<UnitStack>( angel, (uint32_t)5 );
  std::shared_ptr<UnitStack> angel_army_v = std::make_shared<UnitStack>( angel, (uint32_t)5 );

  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 200, .defense_ = 200, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character3 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 100, .defense_ = 100, .power_ = 100, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character4 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( angel_army_john );
  character2->army().recruitUnitStack( angel_army_silverhand );
  character3->army().recruitUnitStack( angel_army_v );
  character4->army().recruitUnitStack( angel_army_panam );

  std::shared_ptr<GridTile> tile = nullptr;
  std::shared_ptr<Battle> battle = std::make_shared<Battle>( character1, character2, tile );
  std::shared_ptr<Battle> battle_v_panam = std::make_shared<Battle>( character3, character4, tile );

  ASSERT_NE( character1->army().getParty()[0], nullptr );
  ASSERT_NE( character3->army().getParty()[0], nullptr );

  battle->attack( angel_army_silverhand, angel_army_john );
  battle_v_panam->attack( angel_army_panam, angel_army_v );

  // when UnitStack is destroyed, its shared_ptr turned into nullptr everywhere globally
  ASSERT_EQ( character1->army().getParty()[0], nullptr );
  ASSERT_EQ( character3->army().getParty()[0], nullptr );
}

TEST( BattleTestMoving, checksettingarmies ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );
  std::shared_ptr<const Unit> swordsman = faction_castle->getUnit( CastleUnitType::SWORDSMAN );
  std::shared_ptr<UnitStack> pikeman_army = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> pikeman_2_army = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> pikeman_3_army = std::make_shared<UnitStack>( pikeman, (uint32_t)30 );
  std::shared_ptr<UnitStack> angel_army = std::make_shared<UnitStack>( angel, (uint32_t)1 );
  std::shared_ptr<UnitStack> swordsman_army = std::make_shared<UnitStack>( swordsman, (uint32_t)2 );
  std::shared_ptr<UnitStack> swordsman_2_army = std::make_shared<UnitStack>( swordsman, (uint32_t)3 );
  std::shared_ptr<UnitStack> swordsman_3_army = std::make_shared<UnitStack>( swordsman, (uint32_t)4 );
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army );
  character1->army().recruitUnitStack( pikeman_2_army );
  character1->army().recruitUnitStack( pikeman_3_army );

  character2->army().recruitUnitStack( angel_army );
  character2->army().recruitUnitStack( swordsman_army );
  character2->army().recruitUnitStack( swordsman_2_army );
  character2->army().recruitUnitStack( swordsman_3_army );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );

  ASSERT_EQ( pikeman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 0u ) )->getObject() );
  ASSERT_EQ( pikeman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 2u ) )->getObject() );
  ASSERT_EQ( pikeman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 4u ) )->getObject() );

  ASSERT_EQ( angel_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 0u ) )->getObject() );
  ASSERT_EQ( swordsman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 2u ) )->getObject() );
  ASSERT_EQ( swordsman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 4u ) )->getObject() );
  ASSERT_EQ( swordsman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 5u ) )->getObject() );
}

TEST( BattleTestMoving, checkmovingarmies ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );
  std::shared_ptr<const Unit> swordsman = faction_castle->getUnit( CastleUnitType::SWORDSMAN );
  std::shared_ptr<UnitStack> pikeman_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> pikeman_2_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> pikeman_3_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> angel_army = std::make_shared<UnitStack>( angel, 1u );
  std::shared_ptr<UnitStack> swordsman_army = std::make_shared<UnitStack>( swordsman, 2u );
  std::shared_ptr<UnitStack> swordsman_2_army = std::make_shared<UnitStack>( swordsman, 3u );
  std::shared_ptr<UnitStack> swordsman_3_army = std::make_shared<UnitStack>( swordsman, 4u );
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army );
  character1->army().recruitUnitStack( pikeman_2_army );
  character1->army().recruitUnitStack( pikeman_3_army );
  character2->army().recruitUnitStack( angel_army );
  character2->army().recruitUnitStack( swordsman_army );
  character2->army().recruitUnitStack( swordsman_2_army );
  character2->army().recruitUnitStack( swordsman_3_army );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  ASSERT_EQ( swordsman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 2u ) )->getObject() );
  ASSERT_EQ( swordsman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 4u ) )->getObject() );
  ASSERT_EQ( swordsman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 5u ) )->getObject() );
  ASSERT_EQ( pikeman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 0u ) )->getObject() );
  ASSERT_EQ( pikeman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 2u ) )->getObject() );
  ASSERT_EQ( pikeman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 4u ) )->getObject() );
  ASSERT_EQ( angel_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 0u ) )->getObject() );
  battle->move( angel_army, CoordPair( 0u, 9u ) );
  ASSERT_EQ( angel_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 9u ) )->getObject() );
}

TEST( BattleTestAttack, check_attacking_armies ) {
  const std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
  std::shared_ptr<const Unit> pikeman = faction_castle->getUnit( CastleUnitType::PIKEMAN );
  std::shared_ptr<const Unit> angel = faction_castle->getUnit( CastleUnitType::ANGEL );
  std::shared_ptr<const Unit> swordsman = faction_castle->getUnit( CastleUnitType::SWORDSMAN );
  std::shared_ptr<UnitStack> pikeman_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> pikeman_2_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> pikeman_3_army = std::make_shared<UnitStack>( pikeman, 30u );
  std::shared_ptr<UnitStack> angel_army = std::make_shared<UnitStack>( angel, 1u );
  std::shared_ptr<UnitStack> swordsman_army = std::make_shared<UnitStack>( swordsman, 2u );
  std::shared_ptr<UnitStack> swordsman_2_army = std::make_shared<UnitStack>( swordsman, 3u );
  std::shared_ptr<UnitStack> swordsman_3_army = std::make_shared<UnitStack>( swordsman, 4u );
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  character1->army().recruitUnitStack( pikeman_army );
  character1->army().recruitUnitStack( pikeman_2_army );
  character1->army().recruitUnitStack( pikeman_3_army );
  character2->army().recruitUnitStack( angel_army );
  character2->army().recruitUnitStack( swordsman_army );
  character2->army().recruitUnitStack( swordsman_2_army );
  character2->army().recruitUnitStack( swordsman_3_army );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );

  battle->move( pikeman_army, CoordPair( 7u, 5u ) );
  battle->move( swordsman_army, CoordPair( 7u, 6u ) );
  battle->attack( pikeman_army, swordsman_army );
  ASSERT_TRUE( swordsman_army->getSize() < 2 );
  ASSERT_TRUE( pikeman_army->getSize() == 30 );
}
