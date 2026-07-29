#include "Battle/Moves/MoveFactory.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <queue>
#include <set>
#include <utility>
#include <vector>

#include "Battle/Battle.h"
#include "Battle/BattleField.h"
#include "Battle/Moves/AttackMove.h"
#include "Battle/Moves/MoveMove.h"
#include "Battle/Moves/WaitMove.h"
#include "Battle/Tile.h"
#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Miscellaneous/Coords.h"
#include "Unit/UnitStack.h"

std::vector<std::shared_ptr<Move>> MoveFactory::createMoveMove( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> valid_moves;
  if ( !battle->getUnitInAction() ) {
    return valid_moves;
  }

  CoordPair start = battle->getUnitInAction()->getCoordsInBattle();
  uint32_t max_steps = battle->getUnitInAction()->getSpeed();

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle->getBattlefield()->getTileByProxy( start );
  if ( !start_tile ) {
    return valid_moves;
  }

  queue.emplace( start_tile, 0U );
  visited.insert( start );
  valid_moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0 ) {
      valid_moves.push_back(
          std::make_shared<MoveMove>( battle->getUnitInAction()->getCoordsInBattle(), current_coords ) );
    }

    if ( cost >= max_steps ) {
      continue;
    }

    for ( const auto& neighbor_tile : battle->battlefield_->getTileNeighbours( current_tile ) ) {
      if ( !neighbor_tile ) {
        continue;
      }

      CoordPair neighbour_coords = neighbor_tile->getCoords();
      // if (visited.count(neighbour_coords)) continue;
      if ( auto it = visited.find( neighbour_coords ); it != visited.end() ) {
        continue;
      }
      if ( neighbor_tile->getObject() ) {
        continue;
      }

      queue.emplace( neighbor_tile, cost + 1 );
      visited.insert( neighbour_coords );
    }
  }
  battle->possible_moves_ = valid_moves;
  return valid_moves;
}

std::vector<std::shared_ptr<Move>> MoveFactory::createAttackMove( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> valid_moves;
  if ( !battle->unit_in_action_ ) {
    return valid_moves;
  }

  CoordPair start = battle->unit_in_action_->getCoordsInBattle();
  uint32_t distance = battle->unit_in_action_->getRange();

  std::queue<std::pair<std::shared_ptr<Tile>, uint32_t>> queue;
  std::set<CoordPair> visited;

  std::shared_ptr<Tile> start_tile = battle->battlefield_->getTileByProxy( start );
  if ( !start_tile ) {
    return valid_moves;
  }

  queue.emplace( start_tile, 0U );
  visited.insert( start );
  std::vector<std::shared_ptr<UnitStack>> target_units = battle->getUnitsInBattle();
  std::shared_ptr<UnitStack> unit;
  valid_moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  while ( !queue.empty() ) {
    auto [current_tile, cost] = queue.front();
    queue.pop();

    const CoordPair current_coords = current_tile->getCoords();
    if ( cost > 0U && cost <= distance && current_tile->getObject() != nullptr ) {
      // some magic to get defending unit
      std::ranges::for_each( target_units,
                             [&unit, &current_coords, &battle]( const std::shared_ptr<UnitStack>& unit_tmp ) {
                               if ( current_coords == unit_tmp->getCoordsInBattle()
                                    && !battle->isSameArmy( battle->getUnitInAction(), unit_tmp ) ) {
                                 unit = unit_tmp;
                               }
                             } );
      if ( unit ) {
        valid_moves.push_back(
            std::make_shared<AttackMove>( battle->unit_in_action_->getCoordsInBattle(), unit->getCoordsInBattle() ) );
      }
    }

    if ( cost >= distance ) {
      continue;
    }

    for ( const auto& neighbor_tile : battle->battlefield_->getTileNeighbours( current_tile ) ) {
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
  battle->possible_moves_ = valid_moves;
  return valid_moves;
}

std::vector<std::shared_ptr<Move>> MoveFactory::generateMoves( std::shared_ptr<Battle> battle ) {
  std::vector<std::shared_ptr<Move>> moves;
  switch ( battle->getBattleState() ) {
    case BattleState::MOVING: {
      moves = createMoveMove( battle );
      break;
    }
    case BattleState::ATTACKING: {
      moves = createAttackMove( battle );
      break;
    }
    case BattleState::WIN_ATTACKER:
    case BattleState::WIN_DEFENDER: {
      err::raise<NotImplementedException>( "" );
      break;
    }
    default: {
      err::raise<UnknownStateException>( "Unknown battle state" );
      break;
    }
  }
  moves.push_back( std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() ) );
  return moves;
}