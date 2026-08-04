#include <gtest/gtest.h>

#include <memory>

#include "Miscellaneous/ProjectLib.h"
#include "Unit/Faction.hpp"
#include "Unit/Unit.h"
#include "Unit/UnitsLib.h"

// TEST( UnitTest, findUnitData ) {
//   std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
//   CastleUnitType unit_type = CastleUnitType::ANGEL;
//   auto unit_data_itr = UNITS_PRESET_CASTLE.find( unit_type );
//   ASSERT_NE( unit_data_itr, UNITS_PRESET_CASTLE.end() );
// }

// TEST( UnitTest, constructor ) {
//   std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
//   CastleUnitType unit_type = CastleUnitType::ANGEL;
//   auto unit_data_ptr = UNITS_PRESET_CASTLE.find( unit_type )->second;  // not .end(), checked in previous test
//   std::shared_ptr<Unit> unit = std::make_shared<Unit>( unit_data_ptr, faction_castle, static_cast<int>( unit_type ) );
//   // no assert, just checking if anything is thrown
// }

// TEST( UnitTest, getters ) {
//   std::shared_ptr<FactionCastle> faction_castle = std::make_shared<FactionCastle>();
//   CastleUnitType unit_type = CastleUnitType::ANGEL;
//   auto unit_data_ptr = UNITS_PRESET_CASTLE.find( unit_type )->second;  // not .end(), checked in previous test
//   std::shared_ptr<Unit> unit = std::make_shared<Unit>( unit_data_ptr, faction_castle, static_cast<int>( unit_type ) );

//   ASSERT_EQ( unit->getName(), unit_data_ptr->name_ );
//   ASSERT_EQ( unit->getLevel(), unit_data_ptr->level_ );
//   ASSERT_EQ( unit->getAttack(), unit_data_ptr->attack_ );
//   ASSERT_EQ( unit->getDefense(), unit_data_ptr->defense_ );
//   ASSERT_EQ( unit->getMinDamage(), unit_data_ptr->min_damage_ );
//   ASSERT_EQ( unit->getMaxDamage(), unit_data_ptr->max_damage_ );
//   ASSERT_EQ( unit->getHealth(), unit_data_ptr->health_ );
//   ASSERT_EQ( unit->getSpeed(), unit_data_ptr->speed_ );
//   ASSERT_EQ( unit->getCounterAttack(), unit_data_ptr->counter_attack_ );
//   ASSERT_EQ( unit->getGrowth(), unit_data_ptr->growth_ );
//   ASSERT_EQ( unit->getCost(), unit_data_ptr->cost_ );
//   // getDmg gets checked later
//   ASSERT_EQ( unit->getRange(), MELEE_UNIT_RANGE );  // range is melee
//   ASSERT_EQ( unit->getFightValue(), unit_data_ptr->fight_value_ );
// }

// TEST( UnitTest, getDmgCalculations ) {

//   // getDmg = min_dmg + rand() % (max_dmg - min_dmg + 1)
//   for ( auto i = 0U; i < 1000; ++i ) {
//     auto dmg_calculated = unit->getDmg();
//     ASSERT_TRUE( dmg_calculated >= unit->getMinDamage() );
//     ASSERT_TRUE( dmg_calculated <= unit->getMaxDamage() );
//   }
// }