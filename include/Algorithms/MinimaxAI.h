#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

class Move;
class CoordPair;
class Battle;
class UnitStack;

/**
 * @details
 * Attacker is the maximizing player, Defender is the minimizing player.
 */

class MinimaxAI {
 private:
  // uint32_t max_depth_;
  static std::pair<std::shared_ptr<Move>, double> doMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                             double alpha, double beta, bool maximizing_player,
                                                             std::shared_ptr<Move> move );
  static std::pair<std::shared_ptr<Move>, double> doMultiMinimax( std::shared_ptr<Battle> battle, uint32_t depth,
                                                                  double alpha, double beta, bool maximizing_player,
                                                                  std::shared_ptr<Move> move );
  static CoordPair centerOfPowerOfArmy( const std::vector<std::shared_ptr<UnitStack>> army );
  static double seekEnemy( std::shared_ptr<Battle> battle, std::shared_ptr<Move> move );
  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
 public:
  static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth );
  static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth, bool maximizing_player );
  static double evaluate( const std::shared_ptr<Battle> battle_state );
};