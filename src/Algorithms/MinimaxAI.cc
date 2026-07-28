#include "Algorithms/MinimaxAI.h"

#include <sys/types.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <execution>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>

#include "Battle/Battle.h"
#include "Battle/Moves/Move.hpp"
#include "Battle/Moves/MoveFactory.h"
#include "Battle/Moves/WaitMove.h"
#include "Miscellaneous/ProjectLib.h"
#include "Unit/UnitStack.h"

std::shared_ptr<Move> MinimaxAI::getBestMove( std::shared_ptr<Battle> battle, uint32_t depth, bool maximizing_player ) {
  std::shared_ptr<WaitMove> move = std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() );
  return doMinimax( battle, depth, -INF_SCORE, INF_SCORE, maximizing_player, move ).first;
}
std::shared_ptr<Move> MinimaxAI::getBestMove( std::shared_ptr<Battle> battle, uint32_t depth ) {
  std::shared_ptr<WaitMove> move = std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() );
  return doMinimax( battle, depth, -INF_SCORE, INF_SCORE,
                    battle->isSameArmy( battle->getUnitInAction(), battle->getAttackingArmy()[0] ), move )
      .first;
}
std::pair<std::shared_ptr<Move>, double> MinimaxAI::doMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                               double alpha, double beta, bool maximizing_player,
                                                               std::shared_ptr<Move> move ) {
  /**
   * @WARNING
   * the @param minimizing_player is trying to get
   *
   * !! AS LOW AS POSSIBLE !!
   *
   * in score
   *
   */

  BattleState state = battle->getState();
  switch ( state ) {
    case ( BattleState::WIN_ATTACKER ): return std::make_pair( move, INF_SCORE );
    case ( BattleState::WIN_DEFENDER ): return std::make_pair( move, -INF_SCORE );
    default: break;
  }
  if ( depth == 0 ) {
    return std::make_pair( move, evaluate( battle ) );
  }
  std::shared_ptr<Battle> battle_copied;
  std::vector<std::shared_ptr<Move>> moves = MoveFactory::generateMoves( battle );
  std::pair<std::shared_ptr<Move>, double> evaluation;
  std::shared_ptr<Move> best_move;

  if ( moves.size() == 0 ) {
    return { move, evaluate( battle ) };
  }

  if ( maximizing_player ) {
    double max_eval = -INF_SCORE;
    if ( moves.size() == 0 ) {
      return std::make_pair( move, evaluate( battle ) );
    }
    for ( auto& move_to_check : moves ) {
      battle_copied = battle->copy();
      move_to_check->execute( battle_copied );
      evaluation = doMinimax( battle_copied, depth - 1, alpha, beta, false, move_to_check );
      evaluation.second += seekEnemy( battle, move_to_check );
      if ( max_eval <= evaluation.second ) {
        max_eval = evaluation.second;
        best_move = move_to_check;
      }
      alpha = std::max( alpha, evaluation.second );
      if ( alpha >= beta ) {
        break;
      }
    }
    return std::make_pair( best_move, max_eval );
  }
  double min_eval = INF_SCORE;
  if ( moves.size() == 0 ) {
    return std::make_pair( move, evaluate( battle ) );
  }
  for ( auto& move_to_check : moves ) {
    battle_copied = battle->copy();
    move_to_check->execute( battle_copied );
    evaluation = doMinimax( battle_copied, depth - 1, alpha, beta, true, move_to_check );
    evaluation.second -= seekEnemy( battle, move_to_check );
    if ( min_eval >= evaluation.second ) {
      min_eval = evaluation.second;
      best_move = move_to_check;
    }
    beta = std::min( beta, evaluation.second );
    if ( alpha >= beta ) {
      break;
    }
  }
  return std::make_pair( best_move, min_eval );
}

std::pair<std::shared_ptr<Move>, double> MinimaxAI::doMultiMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                                    double alpha, double beta, bool maximizing_player,
                                                                    std::shared_ptr<Move> move ) {
  /**
   * @WARNING
   * the @param minimizing_player is trying to get
   *
   * !! AS LOW AS POSSIBLE !!
   *
   * in score
   *
   */

  BattleState state = battle->getState();
  switch ( state ) {
    case ( BattleState::WIN_ATTACKER ): return std::make_pair( move, INF_SCORE );
    case ( BattleState::WIN_DEFENDER ): return std::make_pair( move, -INF_SCORE );
    default: break;
  }
  if ( depth == 0 ) {
    return std::make_pair( move, evaluate( battle ) );
  }
  std::shared_ptr<Battle> battle_copied;
  std::vector<std::shared_ptr<Move>> moves = MoveFactory::generateMoves( battle );
  std::mutex eval_mut;
  std::pair<std::shared_ptr<Move>, double> evaluation;
  std::shared_ptr<Move> best_move;

  if ( moves.size() == 0 ) {
    return { move, evaluate( battle ) };
  }

  if ( maximizing_player ) {
    double max_eval = -INF_SCORE;
    if ( moves.size() == 0 ) {
      return std::make_pair( move, evaluate( battle ) );
    }
    std::for_each( std::execution::par, moves.begin(), moves.end(), [&]( const std::shared_ptr<Move>& move_to_check ) {
      if ( alpha >= beta ) {
        return;
      }
      battle_copied = battle->copy();
      move_to_check->execute( battle_copied );
      evaluation = doMultiMinimax( battle_copied, depth - 1, alpha, beta, false, move_to_check );
      if ( evaluation.second >= 0 ) {
        evaluation.second -= seekEnemy( battle, move_to_check );
      } else {
        evaluation.second += seekEnemy( battle, move_to_check );
      }
      eval_mut.lock();
      if ( max_eval <= evaluation.second ) {
        max_eval = evaluation.second;
        best_move = move_to_check;
      }
      alpha = std::max( alpha, evaluation.second );
      eval_mut.unlock();
      if ( alpha >= beta ) {
        return;
      }
    } );
    return std::make_pair( best_move, max_eval );
  }
  double min_eval = INF_SCORE;
  if ( moves.size() == 0 ) {
    return std::make_pair( move, evaluate( battle ) );
  }
  std::for_each( std::execution::par, moves.begin(), moves.end(), [&]( const std::shared_ptr<Move>& move_to_check ) {
    if ( alpha >= beta ) {
      return;
    }
    battle_copied = battle->copy();
    move_to_check->execute( battle_copied );
    evaluation = doMultiMinimax( battle_copied, depth - 1, alpha, beta, true, move_to_check );
    if ( evaluation.second >= 0 ) {
      evaluation.second += seekEnemy( battle, move_to_check );
    } else {
      evaluation.second -= seekEnemy( battle, move_to_check );
    }
    eval_mut.lock();
    if ( min_eval <= evaluation.second ) {
      min_eval = evaluation.second;
      best_move = move_to_check;
    }
    alpha = std::max( alpha, evaluation.second );
    eval_mut.unlock();
    if ( alpha >= beta ) {
      return;
    }
  } );
  return std::make_pair( best_move, min_eval );
}

double MinimaxAI::evaluate( const std::shared_ptr<Battle> battle_state ) {
  if ( battle_state->getState() == BattleState::WIN_ATTACKER ) {
    return INF_SCORE;
  }
  if ( battle_state->getState() == BattleState::WIN_DEFENDER ) {
    return -INF_SCORE;
  }
  const auto attacking_army = battle_state->getAttackingArmy();
  const auto defending_army = battle_state->getDefendingArmy();

  double fight_value_diff = 0;
  for ( const auto& unit_stack : attacking_army ) {
    fight_value_diff += unit_stack->getEffectiveFightValue();
  }

  for ( const auto& unit_stack : defending_army ) {
    fight_value_diff -= unit_stack->getEffectiveFightValue();
  }

  /*
  if (win && is_maximizing)
    heuristic_val += max_wartosc_atakujacego
  if (win && is_minimizing)
    heuristic_val -= min_wartosc_broniacego
  */

  // throw NotImplementedException( "MinimaxAI::evaluate does not implement a heuristic for win/lose state" );
  return fight_value_diff;
}
CoordPair MinimaxAI::centerOfPowerOfArmy( const std::vector<std::shared_ptr<UnitStack>> army ) {
  double x_nominal = 0, y_nominal = 0, weights = 0;  // NOLINT(readability-isolate-declaration)
  double x_weighted = 0.0, y_weighted = 0.0;         // NOLINT(readability-isolate-declaration)
  std::ranges::for_each( army, [&]( const std::shared_ptr<UnitStack>& unit ) {
    weights += unit->getEffectiveFightValue();
    x_nominal += ( unit->getCoordsInBattle().x_ + 1 ) * unit->getEffectiveFightValue();
    y_nominal += ( unit->getCoordsInBattle().y_ + 1 ) * unit->getEffectiveFightValue();
  } );
  x_weighted = ( x_nominal / weights ) - 1;
  y_weighted = ( y_nominal / weights ) - 1;
  return { static_cast<int>( std::round( x_weighted ) ), static_cast<int>( std::round( y_weighted ) ) };
}

double MinimaxAI::seekEnemy( std::shared_ptr<Battle> battle, std::shared_ptr<Move> move ) {
  std::shared_ptr<UnitStack> seeker = battle->getUnitInAction();
  std::vector<std::shared_ptr<UnitStack>> enemy_army;
  if ( battle->isSameArmy( seeker, battle->getAttackingArmy()[0] ) ) {
    enemy_army = battle->getDefendingArmy();
  } else {
    enemy_army = battle->getAttackingArmy();
  }
  CoordPair to_be_sought = centerOfPowerOfArmy( enemy_army );
  CoordPair move_dest = move->destinationCoords();
  double dist = seeker->getCoordsInBattle().distanceFrom( to_be_sought );
  // if(seeker->getUnit()->getName()=="angel")
  //   std::cout<<"I'm an angel, I'm an angel'"<<std::endl;
  if ( dist == 0 ) {
    return 0.05 * seeker->getEffectiveFightValue();
  }
  return ( 0.05 * seeker->getEffectiveFightValue() * ( dist - move_dest.distanceFrom( to_be_sought ) ) / dist );
}