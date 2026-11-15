#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

class Move;
struct CoordPair;
class Battle;
class UnitStack;

/**
 * @details
 * Attacker is the maximizing player, Defender is the minimizing player.
 */

class MinimaxAI {
 private:
  // uint32_t max_depth_;
  [[nodiscard]] static std::pair<std::shared_ptr<Move>, double> doMinimax( std::shared_ptr<Battle> battle,
                                                                           uint32_t depth, double alpha, double beta,
                                                                           bool maximizing_player,
                                                                           std::shared_ptr<Move> move ) noexcept;
  [[nodiscard]] static std::pair<std::shared_ptr<Move>, double> doMultiMinimax( std::shared_ptr<Battle> battle,
                                                                                uint32_t depth, double alpha,
                                                                                double beta, bool maximizing_player,
                                                                                std::shared_ptr<Move> move ) noexcept;
  [[nodiscard]] static CoordPair centerOfPowerOfArmy( const std::vector<std::shared_ptr<UnitStack>>& army ) noexcept;
  [[nodiscard]] static double seekEnemy( std::shared_ptr<Battle> battle, std::shared_ptr<Move> move ) noexcept;
  // static double evaluator(std::shared_ptr<Battle> battle, std::shared_ptr<Move> move);
 public:
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth ) noexcept;
  [[nodiscard]] static std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle, uint32_t depth,
                                                          bool maximizing_player ) noexcept;
  [[nodiscard]] static double evaluate( const std::shared_ptr<Battle>& battle_state ) noexcept;
};