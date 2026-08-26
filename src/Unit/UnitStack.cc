#include "Unit/UnitStack.h"

#include "Battle/TileObject.hpp"
#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitsLib.h"

UnitStack::UnitStack( const UnitData& data, int size )
    : TileObject( false ), data_( data ), size_( size ), current_health_( data.health_ ), coords_in_battle_( 0, 0 ) {
  if ( size_ <= 0 ) {
    err::raise<UnknownStateException>( "non positive size" );
  }
};

[[nodiscard]] const UnitData& UnitStack::getData() const noexcept {
  return data_;
}

[[nodiscard]] int UnitStack::getMorale() const noexcept {
  return morale_;
}

void UnitStack::setMorale( int new_morale ) noexcept {
  morale_ = new_morale;
}

[[nodiscard]] int UnitStack::getLuck() const noexcept {
  return luck_;
}

void UnitStack::setLuck( int new_luck ) noexcept {
  luck_ = new_luck;
}

[[nodiscard]] int UnitStack::getSize() const noexcept {
  return size_;
}

[[nodiscard]] int UnitStack::getHealthPool() const noexcept {
  return current_health_ + ( data_.get().health_ * size_ );
}

void UnitStack::modifyCurrentHealth( int health_diff ) noexcept {
  int health_pool = current_health_ + ( data_.get().health_ * ( size_ - 1 ) );
  int health_remaining = health_pool - health_diff;
  if ( health_remaining <= 0 ) {
    size_ = 0;
    current_health_ = 0;
    return;
  }
  size_ = ( ( health_remaining ) / data_.get().health_ ) + 1;
  current_health_ = health_remaining - ( ( size_ - 1 ) * data_.get().health_ );
}

[[nodiscard]] bool UnitStack::isAlive() const noexcept {
  return current_health_ > 0;
}

void UnitStack::setCoordsInBattle( CoordPair new_coords ) noexcept {
  coords_in_battle_ = new_coords;
}

[[nodiscard]] CoordPair UnitStack::getCoordsInBattle() const noexcept {
  return coords_in_battle_;
}

[[nodiscard]] UnitStack* UnitStack::asUnit() noexcept {
  return this;
}

// FactionType UnitStack::getFactionType() const {
//   return unit_->getFaction().lock()->getFactionType();
// };

// double UnitStack::getEffectiveFightValue() const {
//   return unit_->getFightValue() * ( ( ( size_ - 1 ) * unit_->getHealth() + current_health_ ) / ( unit_->getHealth() )
//   );
// }

// std::shared_ptr<UnitStack> UnitStack::copy() const {
//   std::shared_ptr<UnitStack> copy = std::make_shared<UnitStack>( this->unit_, this->size_ );
//   copy->coords_in_battle_ = this->coords_in_battle_;
//   copy->morale_ = this->morale_;
//   copy->luck_ = this->luck_;
//   copy->current_health_ = this->current_health_;
//   return copy;
// }