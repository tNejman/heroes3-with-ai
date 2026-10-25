#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "core/Algorithms/IAlgorithm.hpp"
#include "core/Battle/Battle.h"
#include "core/Game/StateBattle.h"
#include "core/Game/UserCommand.h"

class Move;
struct CoordPair;
class Battle;
class UnitStack;

class MCTSAlgorithm : public IAlgorithm {
  class MCTSNode {
   private:
    MCTSNode* parent_ = nullptr;
    int visits_ = 0;
    double score_ = 0.0;
    UserCommand moves_;
    std::vector<MCTSNode> children_;
    void populateNodeWithMoves( std::reference_wrapper<Battle> battle );

   public:
    MCTSNode( MCTSNode& parent, const UserCommand& move );
    void setMoves( const std::vector<UserCommand>& moves );
    [[nodiscard]] MCTSNode* selection() noexcept;
    void backPropagate( double value ) noexcept;
    [[nodiscard]] double rollout() const noexcept;
    MCTSNode* nodeExpansion( std::reference_wrapper<game::StateBattle> state_battle );
    friend class MCTS;
    [[nodiscard]] double uctValue() const noexcept;
  };

 private:
  uint16_t time_limit_{};
  MCTSNode base_node_;

  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
 public:
  MCTSAlgorithm() = delete;
  MCTSAlgorithm( uint16_t time_limit, MCTSNode base_node );
  [[nodiscard]] UserCommand getBestMove( std::reference_wrapper<game::StateBattle> state_battle ) override;
};