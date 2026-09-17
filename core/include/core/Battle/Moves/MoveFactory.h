#pragma once

#include <memory>
#include <vector>

/**
 * @explain
 * Factory class is delegated from class Battle
 * to eliminate circular dependency between Battle and Move classes.
 */

class Move;
class Battle;

class MoveFactory {
 private:
  static std::vector<std::shared_ptr<Move>> createMoveMove( Battle& battle );
  static std::vector<std::shared_ptr<Move>> createAttackMove( Battle& battle );

 public:
  /**
   * @deprecated location of methods
   */
  static std::vector<std::shared_ptr<Move>> generateMoves( Battle& battle );
};
