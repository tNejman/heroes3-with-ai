#include "Unit/UnitStack.h"

#include <cstdint>
#include <memory>
#include <utility>

#include "Miscellaneous/Coords.h"
#include "Miscellaneous/UnitsLib.h"
#include "Unit/Faction.hpp"  // IWYU pragma: keep
#include "Unit/Unit.h"

UnitStack::UnitStack( std::shared_ptr<const Unit> unit, uint32_t size )
    : coords_in_battle_( 0, 0 ),
      unit_( std::move( unit ) ),
      morale_( 0 ),
      luck_( 0 ),
      size_( size ),
      current_health_( unit_->getHealth() ) {};

void UnitStack::setCoordsInBattle( CoordPair new_coords ) {
  this->coords_in_battle_ = new_coords;
}

CoordPair UnitStack::getCoordsInBattle() const {
  return this->coords_in_battle_;
}

uint32_t UnitStack::getSpeed() const {
  return unit_->getSpeed();
};

FactionType UnitStack::getFactionType() const {
  return unit_->getFaction().lock()->getFactionType();
};

int UnitStack::getUnitType() const {
  return unit_->getUnitType();
}
short UnitStack::getMorale() const {
  return morale_;
}
short UnitStack::getLuck() const {
  return luck_;
}
uint32_t UnitStack::getRange() const {
  return unit_->getRange();
}
uint32_t UnitStack::getSize() const {
  return size_;
}
uint32_t UnitStack::getCurrentHealth() const {
  return current_health_;
}
double UnitStack::getEffectiveFightValue() const {
  return unit_->getFightValue() * ( ( ( size_ - 1 ) * unit_->getHealth() + current_health_ ) / ( unit_->getHealth() ) );
}
std::shared_ptr<const Unit> UnitStack::getUnit() const {
  return std::shared_ptr<const Unit>( this->unit_ );
}

bool UnitStack::modifyCurrentHealth( int health_diff ) {
  uint32_t health_pool = current_health_ + getUnit()->getHealth() * ( size_ - 1 );
  int health_remaining = int( health_pool ) - int( health_diff );
  if ( health_remaining <= 0 ) {
    size_ = 0;
    current_health_ = 0;
    return false;
  } else {
    size_ = uint32_t( health_remaining ) / getUnit()->getHealth() + 1;
    current_health_ = uint32_t( health_remaining ) - ( size_ - 1 ) * getUnit()->getHealth();
    return true;
  }
}

uint32_t UnitStack::getHealthPool() const {
  return current_health_ + getUnit()->getHealth() * size_;
}

bool UnitStack::getIfAlive() const {
  return this->current_health_ > 0;
}

std::shared_ptr<UnitStack> UnitStack::copy() const {
  std::shared_ptr<UnitStack> copy = std::make_shared<UnitStack>( this->unit_, this->size_ );
  copy->coords_in_battle_ = this->coords_in_battle_;
  copy->morale_ = this->morale_;
  copy->luck_ = this->luck_;
  copy->current_health_ = this->current_health_;
  return copy;
}

void UnitStack::die() {
  unit_.reset();
  this->~UnitStack();
}