#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

#include "core/Algorithms/IAlgorithm.hpp"

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
  [[nodiscard]] static std::pair<std::shared_ptr<Move>, double> doMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                             double alpha, double beta, bool maximizing_player,
                                                             std::shared_ptr<Move> move );
  [[nodiscard]] static std::pair<std::shared_ptr<Move>, double> doMultiMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                                  double alpha, double beta, bool maximizing_player,
                                                                  std::shared_ptr<Move> move );
  [[nodiscard]] static CoordPair centerOfPowerOfArmy( const std::vector<std::reference_wrapper<UnitStack>> army );
  [[nodiscard]] static double seekEnemy( std::shared_ptr<Battle> battle, std::shared_ptr<Move> move );
  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
 public:
  MinimaxAI() = default;
  MinimaxAI(uint16_t depth);
  [[nodiscard]] std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle);
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth );
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth, bool maximizing_player );
  [[nodiscard]] static double evaluate( const std::shared_ptr<Battle> battle_state );
};