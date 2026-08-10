#include "Game/GameStateBattle.h"

#include <cassert>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Battle/Moves/MoveFactory.h"
#include "Character/Character.h"
#include "Exceptions/Err.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Game/GameCommand.h"
#include "Game/GameContext.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/Coords.h"

StateTransition GameStateBattle::handleMoveStack( const BattleCommand &ms ) noexcept {
  battle_.move( *battle_.getUnitInAction(), ms.destination );
  battle_.setBattleState( BattleState::ATTACKING );
  return NoTransition{};
}
StateTransition GameStateBattle::handleAttackStack( const BattleCommand &as ) noexcept {
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
StateTransition GameStateBattle::handleWait() noexcept {
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

GameStateBattle::GameStateBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                                  std::shared_ptr<GridTile> background )
    : battle_( std::move( attacker ), std::move( defender ), std::move( background ) ) {
}

[[nodiscard]] std::vector<UserCommand> GameStateBattle::legalCommands() const noexcept {
  err::raise<NotImplementedException>();
}

[[nodiscard]] StateTransition GameStateBattle::applyCommand( const UserCommand &command, GameContext & ) noexcept {
  MoveFactory::generateMoves( battle_ );  // updates graphics

  if ( !isLegalCommand( command ) ) {
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
[[nodiscard]] bool GameStateBattle::isLegalCommand( const UserCommand &command ) const noexcept {
  if ( !isCommandForThisState<BattleCommand>( command ) ) {
    return false;
  }
  return battle_.isLegalCommand( std::get<BattleCommand>( command ) );
}

void GameStateBattle::applyGameCommand( const GameCommand &, GameContext & ) noexcept {
  err::raise<NotImplementedException>();
}

void GameStateBattle::accept( IRVisitor &v ) const noexcept {
  v.visit( *this );
}

const Battle &GameStateBattle::viewBattle() const noexcept {
  return battle_;
}