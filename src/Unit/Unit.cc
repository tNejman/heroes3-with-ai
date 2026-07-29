#include "Unit/Unit.h"

#include <cstdint>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>

#include "Battle/TileObject.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Miscellaneous/UnitsLib.h"
#include "Unit/Faction.hpp"

Unit::Unit( const std::shared_ptr<const UnitData> unit_data, const int unit_type )
    : TileObject( false ), unit_data_( std::move( unit_data ) ), unit_type_( unit_type ) {};

Unit::Unit( const std::shared_ptr<const UnitData> unit_data, const std::weak_ptr<Faction> faction, const int unit_type )
    : TileObject( false ), unit_data_( std::move( unit_data ) ), faction_( faction ), unit_type_( unit_type ) {};

const std::string& Unit::getName() const {
  return unit_data_->name_;
}
uint32_t Unit::getLevel() const {
  return unit_data_->level_;
}
uint32_t Unit::getAttack() const {
  return unit_data_->attack_;
}
uint32_t Unit::getDefense() const {
  return unit_data_->defense_;
}
uint32_t Unit::getMinDamage() const {
  return unit_data_->min_damage_;
}
uint32_t Unit::getMaxDamage() const {
  return unit_data_->max_damage_;
}
uint32_t Unit::getHealth() const {
  return unit_data_->health_;
}
uint32_t Unit::getSpeed() const {
  return unit_data_->speed_;
}
uint32_t Unit::getCounterAttack() const {
  return unit_data_->counter_attack_;
}
uint32_t Unit::getGrowth() const {
  return unit_data_->growth_;
}

uint32_t Unit::getCost() const {
  return unit_data_->cost_;
}

uint32_t Unit::getDmg() const {
  return getMinDamage() + ( uint32_t( std::rand() ) % ( getMaxDamage() - getMinDamage() + 1 ) );
}
uint32_t Unit::getRange() const {
  return MELEE_UNIT_RANGE;
}

uint32_t Unit::getFightValue() const {
  return unit_data_->fight_value_;
}
const std::string& Unit::getPathToTexture() const {
  return unit_data_->path_to_texture_;
}
const std::weak_ptr<Faction> Unit::getFaction() const {
  return this->faction_;
};
int Unit::getUnitType() const {
  return this->unit_type_;
}