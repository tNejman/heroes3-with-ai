#include "Battle/Moves/AttackMove.h"

#include <memory>
#include <string>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitStack.h"  // IWYU pragma: keep

AttackMove::AttackMove( CoordPair attacker, CoordPair defender )
    : Move(), attacker_( attacker ), defender_( defender ) {
}

void AttackMove::execute( std::shared_ptr<Battle> battle ) {
  (void)battle->attack( battle->getUnitFromCoords( attacker_ ),
                        battle->getUnitFromCoords( defender_ ) );  // TODO handle return value
  if ( battle->getBattleState() != BattleState::WIN_ATTACKER
       && battle->getBattleState() != BattleState::WIN_DEFENDER ) {
    battle->setBattleState( BattleState::MOVING );
  }
  battle->nextUnit();
}
CoordPair AttackMove::destinationCoords() const {
  return defender_;
}
std::string AttackMove::getPath() const {
  return "Sprites/Battle/Auxiliary/Hexagon_Attack.png";
}

std::string AttackMove::getInfo( std::shared_ptr<Battle> battle ) const {
  std::string info = "Attacker: ";
  info += battle->getUnitFromCoords( attacker_ )->getUnit()->getName();
  info += ", defender: ";
  info += battle->getUnitFromCoords( defender_ )->getUnit()->getName();

  auto x = attacker_.x_;
  auto y = attacker_.y_;
  info += ", old coords: (x=" + std::to_string( x ) + ",y=" + std::to_string( y ) + "), ";

  auto xn = defender_.x_;
  auto yn = defender_.y_;
  info += ", new coords: (x=" + std::to_string( xn ) + ",y=" + std::to_string( yn ) + "), ";

  return info;
}

std::shared_ptr<Move> AttackMove::copy() const {
  return std::make_shared<AttackMove>( attacker_, defender_ );
}