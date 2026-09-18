#include "core/Game/StateBattle.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "aux/Err.hpp"
#include "aux/_NotImplementedException.hpp"
#include "core/Battle/Battle.h"
#include "core/Battle/Moves/Move.hpp"
#include "core/Battle/Moves/MoveFactory.h"
#include "core/Character/Character.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "engine/IGame/Coords.h"
#include "core/Misc/ProjectLib.h"
#include "engine/Graphics/IRVisitor.h"

game::StateTransition game::StateBattle::handleMoveStack( const BattleCommand &ms ) noexcept {
  battle_.move( *battle_.getUnitInAction(), ms.destination );
  battle_.setBattleState( BattleState::ATTACKING );
  return game::NoTransition{};
}
game::StateTransition game::StateBattle::handleAttackStack( const BattleCommand &as ) noexcept {
  auto *attacker = battle_.getUnitInAction();
  auto *defender = battle_.getUnitFromCoords( as.destination );
  battle_.attack( *attacker, *defender );

  if ( battle_.getBattleState() == BattleState::WIN_ATTACKER ) {
    return PopState{};  // TODO actual change
  }
  if ( battle_.getBattleState() == BattleState::WIN_DEFENDER ) {
    return PopState{};  // TODO actual change
  }
  battle_.nextUnit();
  return NoTransition{};
}
game::StateTransition game::StateBattle::handleWait() noexcept {
  if ( battle_.getBattleState() == BattleState::ATTACKING ) {
    battle_.setBattleState( BattleState::MOVING );
    battle_.nextUnit();
  } else if ( battle_.getBattleState() == BattleState::MOVING ) {
    battle_.setBattleState( BattleState::ATTACKING );
  }
  return NoTransition{};
}
// StateTransition GameStateBattle::handleDefend( const Defend & ) noexcept {
//   err::raise<NotImplementedException>();
// }

/* === @PUBLIC === */

game::StateBattle::StateBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                                Terrain background )
    : battle_( std::move( attacker ), std::move( defender ), background ) {
}

[[nodiscard]] std::vector<UserCommand> game::StateBattle::legalCommands() const noexcept {
  err::raise<NotImplementedException>();
}

[[nodiscard]] game::StateTransition game::StateBattle::applyCommand( const UserCommand &command,
                                                                     game::Context & ) noexcept {
  MoveFactory::generateMoves( battle_ );  // updates graphics

  if ( !isLegalCommand( command ) ) {
    // TODO log what got here
    return NoTransition{};
  }
  auto battle_command = std::get<BattleCommand>( command );
  std::cout << battle_command.destination << '\n';
  if ( battle_command.destination == battle_.getUnitInAction()->getCoordsInBattle() ) {
    return handleWait();
  }
  if ( battle_.getBattleState() == BattleState::ATTACKING ) {
    return handleAttackStack( battle_command );
  }
  if ( battle_.getBattleState() == BattleState::MOVING ) {
    return handleMoveStack( battle_command );
  }
  assert( false && "GameStateBattle::applyCommand -> unexpected state" );
  // return std::visit( Overload{ [&]( const MoveStack &ms ) -> StateTransition { return handleMoveStack( ms ); },
  //                              [&]( const AttackStack &as ) -> StateTransition { return handleAttackStack( as ); },
  //                              [&]( const Wait &w ) -> StateTransition { return handleWait( w ); },
  //                              [&]( const Defend &d ) -> StateTransition { return handleDefend( d ); } },
  //                    std::get<BattleCommand>( command ) );
}
[[nodiscard]] bool game::StateBattle::isLegalCommand( const UserCommand &command ) const noexcept {
  if ( !isCommandForThisState( command ) ) {
    return false;
  }
  return battle_.isLegalCommand( std::get<BattleCommand>( command ) );
}

void game::StateBattle::applySystemCommand( const SystemCommand &, game::Context & ) noexcept {
  err::raise<NotImplementedException>();
}

void game::StateBattle::accept( IRVisitor &v ) const noexcept {
  v.visit( *this );
}

const Battle &game::StateBattle::viewBattle() const noexcept {
  return battle_;
}