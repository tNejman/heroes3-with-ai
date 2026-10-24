#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "core/Algorithms/IAlgorithm.hpp"
#include "core/Battle/Battle.h"

class Move;
struct CoordPair;
class Battle;
class UnitStack;
class MCTSNode;

class MCTSAlgorithm : public IAlgorithm{
  class MCTSNode{
    private:
      const MCTSNode* parent_ = nullptr;
      int visits_ = 0;
      float score_ = 0.0F;
      std::shared_ptr<Move> move_;
      std::vector<MCTSNode> children_;
      void populateNodeWithMoves(std::reference_wrapper<Battle> battle);
      [[nodiscard]] double nodeUCTValue() const;
    public:
    MCTSNode(MCTSNode const &parent, std::shared_ptr<Move> move);
    friend class MCTS;
  };
  private:
    uint16_t time_limit_{};
    MCTSNode base_node_;
    
  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
  public:
    MCTSAlgorithm() = delete;
    MCTSAlgorithm(uint16_t time_limit, MCTSNode base_node);
    [[nodiscard]] std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle ) override;


  
};