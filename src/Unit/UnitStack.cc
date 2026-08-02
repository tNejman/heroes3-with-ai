#include "Unit/UnitStack.h"

#include <cstdint>
#include <memory>

#include "Battle/TileObject.hpp"
#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"
#include "Unit/Faction.hpp"  // IWYU pragma: keep
#include "Unit/UnitsLib.h"

UnitStack::UnitStack( const UnitData& unit, uint32_t size )
    : TileObject( false ),
      coords_in_battle_( 0, 0 ),
      data_( unit ),
      morale_( 0 ),
      luck_( 0 ),
      size_( size ),
      current_health_( data_.get().health_ ) {};

void UnitStack::setCoordsInBattle( CoordPair new_coords ) {
  this->coords_in_battle_ = new_coords;
}

CoordPair UnitStack::getCoordsInBattle() const {
  return this->coords_in_battle_;
}

// uint32_t UnitStack::getSpeed() const {
//   return unit_->getSpeed();
// };

// FactionType UnitStack::getFactionType() const {
//   return unit_->getFaction().lock()->getFactionType();
// };

// int UnitStack::getUnitType() const {
//   return unit_->getUnitType();
// }
// short UnitStack::getMorale() const {
//   return morale_;
// }
// short UnitStack::getLuck() const {
//   return luck_;
// }
// uint32_t UnitStack::getRange() const {
//   return unit_->getRange();
// }
// uint32_t UnitStack::getSize() const {
//   return size_;
// }
// uint32_t UnitStack::getCurrentHealth() const {
//   return current_health_;
// }
// double UnitStack::getEffectiveFightValue() const {
//   return unit_->getFightValue() * ( ( ( size_ - 1 ) * unit_->getHealth() + current_health_ ) / ( unit_->getHealth() )
//   );
// }
// std::shared_ptr<const Unit> UnitStack::getUnit() const {
//   return std::shared_ptr<const Unit>( this->unit_ );
// }

bool UnitStack::modifyCurrentHealth( int health_diff ) {
  int health_pool = current_health_ + ( data_.get().health_ * ( size_ - 1 ) );
  int health_remaining = health_pool - health_diff;
  if ( health_remaining <= 0 ) {
    size_ = 0;
    current_health_ = 0;
    return false;
  }
  size_ = ( health_remaining / data_.get().health_ ) + 1;
  current_health_ = health_remaining - ( ( size_ - 1 ) * data_.get().health_ );
  return true;
}

int UnitStack::getHealthPool() const {
  return current_health_ + ( data_.get().health_ * size_ );
}

bool UnitStack::getIfAlive() const {
  return this->current_health_ > 0;
}

std::shared_ptr<UnitStack> UnitStack::copy() const {
  std::shared_ptr<UnitStack> copy = std::make_shared<UnitStack>( this->data_, this->size_ );
  copy->coords_in_battle_ = this->coords_in_battle_;
  copy->morale_ = this->morale_;
  copy->luck_ = this->luck_;
  copy->current_health_ = this->current_health_;
  return copy;
}