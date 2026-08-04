#include "Battle/Moves/WaitMove.h"

#include <memory>
#include <optional>
#include <string>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Miscellaneous/Coords.h"

WaitMove::WaitMove( CoordPair coords ) : Move(), coords_( coords ) {
}

void WaitMove::execute( std::shared_ptr<Battle> battle ) {
  coords_ = battle->getUnitInAction()->getCoordsInBattle();
  if ( battle->getBattleState() == BattleState::ATTACKING ) {
    battle->setBattleState( BattleState::MOVING );
    battle->nextUnit();
  } else if ( battle->getBattleState() == BattleState::MOVING ) {
    battle->setBattleState( BattleState::ATTACKING );
  }
}

std::string WaitMove::getInfo( std::shared_ptr<Battle> battle ) const {
  if ( battle->getUnitFromCoords( coords_ ) == nullptr ) {
    return "no one is waiting in this position";
  }
  std::string info = "Unit: ";
  info += battle->getUnitFromCoords( coords_ )->getData().name_;
  info += " passes their turn";
  info += ", coords: (x=" + std::to_string( coords_.x_ ) + ",y=" + std::to_string( coords_.y_ ) + ")";
  return info;
}
CoordPair WaitMove::destinationCoords() const {
  return coords_;
}
std::string WaitMove::getPath() const {
  return "Sprites/Battle/Auxiliary/Hexagon_Movement.png";
}
std::shared_ptr<Move> WaitMove::copy() const {
  return std::make_shared<WaitMove>( coords_ );
}