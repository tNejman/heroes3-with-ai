#include "core/Algorithms/MCTSAlgorithm.h"

#include <sys/types.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <execution>
#include <functional>
#include <memory>
#include <mutex>
#include <utility>
#include <vector>
#include <chrono>

#include "core/Battle/Battle.h"
#include "core/Battle/Moves/Move.hpp"
#include "core/Battle/Moves/MoveFactory.h"
#include "core/Battle/Moves/WaitMove.h"
#include "core/Misc/ProjectLib.h"
#include "core/Unit/UnitStack.h"

constexpr inline double INF_SCORE = 1e9;
constexpr inline char ITER_CHECKER = 127;//after that many iterations loop will check time

MCTSAlgorithm::MCTSAlgorithm(uint16_t time_limit, MCTSNode base_node) : time_limit_(time_limit), base_node_(std::move(base_node)){};

MCTSAlgorithm::MCTSNode::MCTSNode(MCTSNode const &parent, std::shared_ptr<Move> move) : parent_(&parent), move_(std::move(move)), children_() {}

std::shared_ptr<Move> MCTSAlgorithm::getBestMove(std::shared_ptr<Battle> battle){
  std::shared_ptr<WaitMove> move = std::make_shared<WaitMove>( battle->getUnitInAction()->getCoordsInBattle() );
  base_node_;
  //start timer
  int iterations = 0;
  auto time_limit = std::chrono::milliseconds(time_limit_);
  auto start_time = std::chrono::steady_clock::now();
  // every ITER_CHECKER we check whether we are out of time 
  while(!(((iterations++ & ITER_CHECKER) == 0) && (std::chrono::steady_clock::now() - start_time >= time_limit))){

  }
  return move;
}

void MCTSAlgorithm::MCTSNode::populateNodeWithMoves(std::reference_wrapper<Battle> battle){

}

double MCTSAlgorithm::MCTSNode::nodeUCTValue() const{
  
  //not explored node
  if(visits_ == 0) {
    return INF_SCORE;//pick instantly
  }

}