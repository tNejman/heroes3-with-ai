#include "core/Game/StateBattle.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <magic_enum/magic_enum.hpp>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "aux/Err.hpp"
#include "aux/_NotImplementedException.hpp"
#include "core/Battle/Battle.h"
#include "core/Battle/BattleField.h"
#include "core/Battle/Tile.h"
#include "core/Character/Character.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/IRVisitor.h"

[[nodiscard]] std::vector<BattleCommand> game::StateBattle::createMoveCommands() const noexcept {
  std::vector<BattleCommand> valid_moves;
  if ( battle_.getUnitInAction() == nullptr ) {
    return valid_moves;
  }

  CoordPair start = battle_.getUnitInAction()->getCoordsInBattle();
  auto max_steps = static_cast<uint32_t>( battle_.getUnitInAction()->getData().speed_ );

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle_.getBattlefield()->getTileByProxy( start );
  if ( !start_tile ) {
    return valid_moves;
  }

  queue.emplace( start_tile, 0U );
  visited.insert( start );
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0 ) {
      valid_moves.push_back( BattleCommand{ .action = BattleCommand::Action::MOVE, .destination = current_coords } );
    }

    if ( cost >= max_steps ) {
      continue;
    }

    for ( const auto &neighbor_tile : battle_.getBattlefield()->getTileNeighbours( current_tile ) ) {
      if ( !neighbor_tile ) {
        continue;
      }

      CoordPair neighbour_coords = neighbor_tile->getCoords();
      // if (visited.count(neighbour_coords)) continue;
      if ( auto it = visited.find( neighbour_coords ); it != visited.end() ) {
        continue;
      }
      if ( neighbor_tile->getObject() != nullptr ) {
        continue;
      }

      queue.emplace( neighbor_tile, cost + 1 );
      visited.insert( neighbour_coords );
    }
  }
  return valid_moves;
}

[[nodiscard]] std::vector<BattleCommand> game::StateBattle::createAttackCommands() const noexcept {
  std::vector<BattleCommand> valid_moves;
  if ( battle_.getUnitInAction() == nullptr ) {
    return valid_moves;
  }

  CoordPair start = battle_.getUnitInAction()->getCoordsInBattle();
  uint32_t distance = ( battle_.getUnitInAction()->getData().is_range_ ) ? std::numeric_limits<uint32_t>::max() : 1;

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle_.getBattlefield()->getTileByProxy( start );
  if ( !start_tile ) {
    return valid_moves;
  }

  queue.emplace( start_tile, 0U );
  visited.insert( start );
  auto target_units = battle_.getUnitsInBattle();
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0U && cost <= distance && current_tile->getObject() != nullptr ) {
      // some magic to get defending unit
      std::ranges::for_each( target_units, [&]( const UnitStack &unit_on_battlefield ) {
        if ( current_coords == unit_on_battlefield.getCoordsInBattle()
             && !battle_.isSameArmy( *battle_.getUnitInAction(), unit_on_battlefield ) ) {
          valid_moves.push_back( BattleCommand{ .action = BattleCommand::Action::ATTACK,
                                                .destination = unit_on_battlefield.getCoordsInBattle() } );
        }
      } );
    }

    if ( cost >= distance ) {
      continue;
    }

    for ( const auto &neighbor_tile : battle_.getBattlefield()->getTileNeighbours( current_tile ) ) {
      if ( !neighbor_tile ) {
        continue;
      }

      CoordPair neighbour_coords = neighbor_tile->getCoords();
      // if (visited.count(neighbour_coords)) continue;
      if ( auto it = visited.find( neighbour_coords ); it != visited.end() ) {
        continue;
      }
      // if (neighbor_tile->getObject()) continue;

      queue.emplace( neighbor_tile, cost + 1 );
      visited.insert( neighbour_coords );
    }
  }
  return valid_moves;
}

[[nodiscard]] std::vector<BattleCommand> game::StateBattle::createWaitCommands() const noexcept {
  return { BattleCommand{ .action = BattleCommand::Action::WAIT,
                          .destination = battle_.getUnitInAction()->getCoordsInBattle() } };
}

game::StateTransition game::StateBattle::handleMoveStack( const BattleCommand &ms ) noexcept {
  battle_.move( *battle_.getUnitInAction(), ms.destination );
  battle_.setBattleState( BattleState::ATTACKING );
  return game::NoTransition{};
}
game::StateTransition game::StateBattle::handleAttackStack( const BattleCommand &as ) noexcept {
  auto *attacker = battle_.getUnitInAction();
  auto *defender = battle_.getUnitFromCoords( as.destination );
  battle_.attack( *attacker, *defender );

  if ( battle_.getState() == BattleState::WIN_ATTACKER ) {
    return PopState{};  // TODO actual change
  }
  if ( battle_.getState() == BattleState::WIN_DEFENDER ) {
    return PopState{};  // TODO actual change
  }
  battle_.nextUnit();
  return NoTransition{};
}
game::StateTransition game::StateBattle::handleWait() noexcept {
  if ( battle_.getState() == BattleState::ATTACKING ) {
    battle_.setBattleState( BattleState::MOVING );
    battle_.nextUnit();
  } else if ( battle_.getState() == BattleState::MOVING ) {
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
  // @TODO add cacheing

  std::vector<BattleCommand> legal_commands;

  switch ( battle_.getState() ) {
    case BattleState::MOVING:
      legal_commands.append_range( this->createMoveCommands() );
      legal_commands.append_range( this->createWaitCommands() );
      break;
    case BattleState::ATTACKING:
      legal_commands.append_range( this->createAttackCommands() );
      legal_commands.append_range( this->createWaitCommands() );
      break;
    default:
      err::abort( "illegal to get legalCommands in state: "
                  + std::string{ magic_enum::enum_name( battle_.getState() ) } );
  }

  return { legal_commands.begin(), legal_commands.end() };
}

[[nodiscard]] game::StateTransition game::StateBattle::applyCommand( const UserCommand &command,
                                                                     game::Context & ) noexcept {
  // MoveFactory::generateMoves( battle_ );  // updates graphics
  battle_.setPossibleMoves( this->legalCommands() );

  if ( !isLegalCommand( command ) ) {
    // TODO log what got here
    return NoTransition{};
  }
  auto battle_command = std::get<BattleCommand>( command );
  std::cout << battle_command.destination << '\n';
  if ( battle_command.destination == battle_.getUnitInAction()->getCoordsInBattle() ) {
    return handleWait();
  }
  if ( battle_.getState() == BattleState::ATTACKING ) {
    return handleAttackStack( battle_command );
  }
  if ( battle_.getState() == BattleState::MOVING ) {
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