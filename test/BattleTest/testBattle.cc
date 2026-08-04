#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <optional>

#include "Battle/Battle.h"
#include "Battle/Tile.h"
#include "Character/Character.h"
#include "Character/CharacterBuilder.h"
#include "Character/CharacterStats.h"
#include "Graphics/Visitor.h"
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
  UnitStack pikeman_army{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 };
  UnitStack angel_army{ getCastleUnit( CastleUnitType::ANGEL ), 1 };

  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  auto& pikeman_ref = character1->army().recruitUnitStack( pikeman_army );
  auto& angel_ref = character2->army().recruitUnitStack( angel_army );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  battle->attack( pikeman_ref, angel_ref );
  ASSERT_EQ( angel_ref.getSize(), 1 );
  battle->attack( angel_ref, pikeman_ref );
  ASSERT_TRUE( pikeman_ref.getSize() < 30 );
}

TEST( BattleTest, checkingattacking ) {
  std::shared_ptr<Character> character1 =
      CharacterBuilder{}
          .setName( "John" )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 10, .defense_ = 10, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character2 =
      CharacterBuilder{}
          .setName( "Silverhand" )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character3 =
      CharacterBuilder{}
          .setName( "V" )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 100, .defense_ = 100, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();
  std::shared_ptr<Character> character4 =
      CharacterBuilder{}
          .setName( "Panam" )
          .setStats( CharacterStats{
              CharacterStats::PrimarySkills{ .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 },
              CharacterStats::Misc{ .morale_ = 2, .luck_ = -3 } } )
          .buildSharedPtr();

  auto& pikeman_john_ref =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& angel_silverhand_ref =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& angel_v_ref = character3->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& pikeman_panam_ref =
      character4->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  std::unique_ptr<Battle> battle_v_panam = std::make_unique<Battle>( character3, character4, tile );

  battle->attack( pikeman_john_ref, angel_silverhand_ref );
  ASSERT_EQ( angel_silverhand_ref.getSize(), 1 );
  battle->attack( angel_silverhand_ref, pikeman_john_ref );
  ASSERT_TRUE( pikeman_john_ref.getSize() < 30 );
  battle_v_panam->attack( angel_v_ref, pikeman_panam_ref );
  ASSERT_TRUE( pikeman_john_ref.getHealthPool() > pikeman_panam_ref.getHealthPool() );
}

TEST( BattleTest, checkingMaxattackBonus ) {
  std::shared_ptr<Character> character1 =
      CharacterBuilder{}
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

  auto& pikeman_john_ref =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& angel_silverhand_ref =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& angel_v_ref = character3->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& pikeman_panam_ref =
      character4->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  std::unique_ptr<Battle> battle_v_panam = std::make_unique<Battle>( character3, character4, tile );

  battle->attack( angel_silverhand_ref, pikeman_john_ref );
  ASSERT_TRUE( pikeman_john_ref.getSize() < 30 );
  battle_v_panam->attack( angel_v_ref, pikeman_panam_ref );
  ASSERT_TRUE( pikeman_panam_ref.getSize() < 30 );
  ASSERT_EQ( pikeman_john_ref.getHealthPool(), pikeman_panam_ref.getHealthPool() );
}

TEST( BattleTest, checkingMaxdefenseBonus ) {
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
  auto& angel_john_ref = character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 5 } );
  auto& angel_silverhand_ref =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 5 } );
  auto& angel_v_ref = character3->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 5 } );
  auto& angel_panam_ref = character4->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 5 } );

  std::shared_ptr<GridTile> tile = nullptr;
  std::shared_ptr<Battle> battle = std::make_shared<Battle>( character1, character2, tile );
  std::shared_ptr<Battle> battle_v_panam = std::make_shared<Battle>( character3, character4, tile );

  ASSERT_NE( character1->army().getParty()[0], std::nullopt );
  ASSERT_NE( character3->army().getParty()[0], std::nullopt );

  battle->attack( angel_silverhand_ref, angel_john_ref );
  battle_v_panam->attack( angel_panam_ref, angel_v_ref );

  // when UnitStack is destroyed, its shared_ptr turned into nullptr everywhere globally
  ASSERT_EQ( character1->army().getParty()[0], std::nullopt );
  ASSERT_EQ( character3->army().getParty()[0], std::nullopt );
}

TEST( BattleTestMoving, checksettingarmies ) {
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  auto& pikeman_army = character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_2_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_3_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );

  auto& angel_army = character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& swordsman_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 2 } );
  auto& swordsman_2_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 3 } );
  auto& swordsman_3_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 4 } );
  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );

  ASSERT_EQ( &pikeman_army, battle->getBattlefield()->getTileByProxy( { 0, 0 } )->getObject() );
  ASSERT_EQ( &pikeman_2_army, battle->getBattlefield()->getTileByProxy( { 0, 2 } )->getObject() );
  ASSERT_EQ( &pikeman_3_army, battle->getBattlefield()->getTileByProxy( { 0, 4 } )->getObject() );

  ASSERT_EQ( &angel_army, battle->getBattlefield()->getTileByProxy( { 14, 0 } )->getObject() );
  ASSERT_EQ( &swordsman_army, battle->getBattlefield()->getTileByProxy( { 14, 2 } )->getObject() );
  ASSERT_EQ( &swordsman_2_army, battle->getBattlefield()->getTileByProxy( { 14, 4 } )->getObject() );
  ASSERT_EQ( &swordsman_3_army, battle->getBattlefield()->getTileByProxy( { 14, 5 } )->getObject() );
}

TEST( BattleTestMoving, checkmovingarmies ) {
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  auto& pikeman_army = character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_2_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_3_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );

  auto& angel_army = character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& swordsman_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 2 } );
  auto& swordsman_2_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 3 } );
  auto& swordsman_3_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 4 } );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );
  ASSERT_EQ( &swordsman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 2u ) )->getObject() );
  ASSERT_EQ( &swordsman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 4u ) )->getObject() );
  ASSERT_EQ( &swordsman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 5u ) )->getObject() );
  ASSERT_EQ( &pikeman_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 0u ) )->getObject() );
  ASSERT_EQ( &pikeman_2_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 2u ) )->getObject() );
  ASSERT_EQ( &pikeman_3_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 4u ) )->getObject() );
  ASSERT_EQ( &angel_army, battle->getBattlefield()->getTileByProxy( CoordPair( 14u, 0u ) )->getObject() );
  battle->move( angel_army, CoordPair( 0u, 9u ) );
  ASSERT_EQ( &angel_army, battle->getBattlefield()->getTileByProxy( CoordPair( 0u, 9u ) )->getObject() );
}

TEST( BattleTestAttack, check_attacking_armies ) {
  std::shared_ptr<Character> character1 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();
  std::shared_ptr<Character> character2 = CharacterBuilder{}
                                              .setStats( CharacterStats{ CharacterStats::PrimarySkills{
                                                  .attack_ = 0, .defense_ = 0, .power_ = 10, .knowledge_ = 10 } } )
                                              .buildSharedPtr();

  auto& pikeman_army = character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_2_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );
  auto& pikeman_3_army =
      character1->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::PIKEMAN ), 30 } );

  auto& angel_army = character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::ANGEL ), 1 } );
  auto& swordsman_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 2 } );
  auto& swordsman_2_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 3 } );
  auto& swordsman_3_army =
      character2->army().recruitUnitStack( UnitStack{ getCastleUnit( CastleUnitType::SWORDSMAN ), 4 } );

  std::shared_ptr<GridTile> tile = nullptr;
  std::unique_ptr<Battle> battle = std::make_unique<Battle>( character1, character2, tile );

  battle->move( pikeman_army, CoordPair( 7u, 5u ) );
  battle->move( swordsman_army, CoordPair( 7u, 6u ) );
  battle->attack( pikeman_army, swordsman_army );
  ASSERT_TRUE( swordsman_army.getSize() < 2 );
  ASSERT_TRUE( pikeman_army.getSize() == 30 );
}
