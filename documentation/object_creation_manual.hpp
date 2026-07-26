/* ===========================

DO NOT BUILD THIS FILE

=========================== */

// Manual on how to create objects in Heroes3App

#include <memory>
#include <cassert>

#include <Units/Faction.hpp>
#include <Units/UnitStack.h>
#include <Miscellaneous/ProjectLib.h>

/* ===== 1. Faction =====
pattern:
const std::shared_ptr<FactionT> f = std::make_shared<FactionT>();
    where FactionT has to be replaced with a concrete child of Faction
    and possible values of Faction are [FactionForge, FactionConflux, FactionCastle]

Dependencies to create: N/A
*/
// e.g.
const std::shared_ptr<FactionForge> faction_forge_ptr = std::make_shared<FactionForge>();


/* ===== 2. Unit =====
pattern:
const std::shared_ptr<const Unit> u = f->getUnit(FactionUnitEnum::UNIT_NAME);
    where FactionUnitEnum is an enumerate differing, based on what concrete class is being used

Dependencies to create: shared_ptr<FactionT>
*/    
// e.g.
const std::shared_ptr<const Unit> grunt = faction_forge_ptr->getUnit(ForgeUnitType::GRUNT);


/* ===== 3. UnitStack =====
pattern:
std::shared_ptr<UnitStack> us = std::make_shared<UnitStack>(std::shared_ptr<const Unit>(unit1), count);
    where unit1 is an existing shared_ptr<const Unit>
    and count is a size_t value

Dependencies to create: shared_ptr<const Unit>
*/
// e.g.
std::shared_ptr<UnitStack> unit_stack1 = std::make_shared<UnitStack>(std::shared_ptr<const Unit>(grunt), 30);


/* ===== 4. Character =====
pattern:
std::shared_ptr<Character> c = std::make_shared<Character>(
    string name, CoordPair({x,y}), uint attack, uint defense, uint power, uint knowledge, uint max_mana, int morale, int luck)

Dependencies to create: N/A
*/
// e.g.
std::shared_ptr<Character> hero1 = std::make_shared<Character>("John", CoordPair({0,0}), 10, 12, 15, 3, 50, -1, -2);
