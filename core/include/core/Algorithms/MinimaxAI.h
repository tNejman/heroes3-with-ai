#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "core/Algorithms/IAlgorithm.hpp"
#include "core/Game/StateBattle.h"

class Move;
struct CoordPair;
class Battle;
class UnitStack;

/**
 * @details
 * Attacker is the maximizing player, Defender is the minimizing player.
 */

class MinimaxAI : public IAlgorithm{
 private:
  uint16_t depth_;
  [[nodiscard]] static std::pair<std::shared_ptr<Move>, double> doMinimax( std::reference_wrapper<Battle> battle, uint32_t depth,
                                                             double alpha, double beta, bool maximizing_player,
                                                             std::shared_ptr<Move> move );
  [[nodiscard]] static std::pair<std::reference_wrapper<Move>, double> doMultiMinimax( std::reference_wrapper<Battle> battle, uint32_t depth,
                                                                    double alpha, double beta, bool maximizing_player,
                                                                    std::reference_wrapper<Move> move );
  [[nodiscard]] static CoordPair centerOfPowerOfArmy( std::vector<std::reference_wrapper<UnitStack>> army );
  [[nodiscard]] static double seekEnemy( std::reference_wrapper<Battle> battle, std::shared_ptr<Move> move );
  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
 public:
  //MinimaxAI() = default;
  MinimaxAI(uint16_t depth);
  [[nodiscard]] UserCommand getBestMove( std::reference_wrapper<game::StateBattle> state_battle ) override;
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::reference_wrapper<Battle> battle, uint32_t depth );
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::reference_wrapper<Battle> battle, uint32_t depth, bool maximizing_player );
  [[nodiscard]] static double evaluate( std::reference_wrapper<Battle> battle_state );
};