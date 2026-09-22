#include "core/Battle/Moves/AttackMove.h"

#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <string>

#include "aux/Err.hpp"
#include "core/Battle/Battle.h"
#include "core/Battle/Moves/Move.hpp"
#include "core/Exceptions/UnknownStateException.hpp"
#include "core/Unit/UnitStack.h"  // IWYU pragma: keep
#include "engine/IGame/Coords.h"


AttackMove::AttackMove( CoordPair attacker, CoordPair defender )
    : Move(), attacker_( attacker ), defender_( defender ) {
}

void AttackMove::execute( std::shared_ptr<Battle> battle ) {
  auto* maybe_attacker = battle->getUnitFromCoords( attacker_ );
  auto* maybe_defender = battle->getUnitFromCoords( defender_ );
  if ( maybe_attacker == nullptr ) {
    err::raise<UnknownStateException>( "attacker is null" );
  } else if ( maybe_defender == nullptr ) {
    err::raise<UnknownStateException>( "defender is null" );
  }

  battle->attack( *( maybe_attacker->asUnit() ), *( maybe_defender->asUnit() ) );
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
  info += std::visit( []( const auto& unit_type ) { return magic_enum::enum_name( unit_type ); },
                      battle->getUnitFromCoords( attacker_ )->getData().type_ );
  info += ", defender: ";
  info += std::visit( []( const auto& unit_type ) { return magic_enum::enum_name( unit_type ); },
                      battle->getUnitFromCoords( defender_ )->getData().type_ );

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