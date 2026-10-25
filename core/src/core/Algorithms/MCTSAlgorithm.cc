#include "core/Algorithms/MCTSAlgorithm.h"

#include <sys/types.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <execution>
#include <functional>
#include <memory>
#include <mutex>
#include <numbers>
#include <utility>
#include <vector>

#include "core/Battle/Battle.h"
#include "core/Game/StateBattle.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"

constexpr inline double INF_SCORE = 1e9;
constexpr inline char ITER_CHECKER = 127;  // after that many iterations loop will check time
constexpr inline double CP_CONSTANT = 2 * ( 1 / std::numbers::sqrt2 );

MCTSAlgorithm::MCTSAlgorithm( uint16_t time_limit, MCTSNode base_node )
    : time_limit_( time_limit ), base_node_( std::move( base_node ) ) {};

MCTSAlgorithm::MCTSNode::MCTSNode( MCTSNode& parent, const UserCommand& move ) : parent_( &parent ), moves_( move ) {};

void MCTSAlgorithm::MCTSNode::setMoves( const std::vector<UserCommand>& moves ) {
  for ( const auto& move : moves ) {
    this->children_.emplace_back( *this, move );
  }
}

double MCTSAlgorithm::MCTSNode::uctValue() const noexcept {
  assert( !parent_ );
  // first time
  if ( visits_ == 0 ) {
    return INF_SCORE;  // pick instantly
  }
  return ( score_ / static_cast<double>( visits_ ) )
         + ( CP_CONSTANT * sqrt( 2 * std::log( parent_->visits_ ) / visits_ ) );
}

MCTSAlgorithm::MCTSNode* MCTSAlgorithm::MCTSNode::selection() noexcept {
  MCTSNode* current = this;
  double best_uct = 0.0;
  double tmp_uct = NAN;
  while ( !current->children_.empty() ) {
    MCTSNode* best_child = &current->children_.front();
    best_uct = 0.0;

    for ( auto& child : current->children_ ) {
      tmp_uct = child.uctValue();
      if ( tmp_uct > best_uct ) {
        best_child = &child;
        best_uct = tmp_uct;
        if ( best_uct == INF_SCORE ) {
          break;  // we chose unseen node
        }
      }
    }
    current = best_child;
  }
  return current;
}

MCTSAlgorithm::MCTSNode* MCTSAlgorithm::MCTSNode::nodeExpansion(
    std::reference_wrapper<game::StateBattle> state_battle ) {
  assert( children_.empty() );
  if ( visits_ != 0 ) {
    this->setMoves( state_battle.get().legalCommands() );
  }
  if ( children_.empty() ) {
    return this;  // we are in terminal state
  }
  return &children_.front();
}

double MCTSAlgorithm::MCTSNode::rollout() const noexcept {
  //@TODO add true rollout policy
  return this->score_;
}

void MCTSAlgorithm::MCTSNode::backPropagate( double value ) noexcept {
  MCTSNode* current = this;
  current->score_ += value;
  current->visits_++;
  while ( parent_ != nullptr ) {
    current = parent_;
    current->score_ += value;
    current->visits_++;
  }
}

UserCommand MCTSAlgorithm::getBestMove( std::reference_wrapper<game::StateBattle> state_battle ) {
  auto move = BattleCommand{
      .action = BattleCommand::Action::WAIT,
      .destination = state_battle.get().viewBattle().getUnitInAction()->getCoordsInBattle(),
  };
  base_node_.setMoves( state_battle.get().legalCommands() );
  // start timer
  int iterations = 0;
  auto time_limit = std::chrono::milliseconds( time_limit_ );
  auto start_time = std::chrono::steady_clock::now();
  MCTSNode* current = nullptr;
  double value = NAN;
  // every ITER_CHECKER we check whether we are out of time
  while ( ( ( iterations++ & ITER_CHECKER ) != 0 )
          || !( std::chrono::steady_clock::now() - start_time >= time_limit ) ) {
    current = base_node_.selection();
    current = current->nodeExpansion( state_battle );
    value = current->rollout();
    current->backPropagate( value );
  }
  return move;
}
