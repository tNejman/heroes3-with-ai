#pragma once

#include <memory>
#include <vector>

#include "Battle/Moves/AttackMove.h"
#include "Battle/Moves/MoveMove.h"
#include "Battle/Moves/WaitMove.h"

/**
 * @explain
 * Factory class is delegated from class Battle
 * to eliminate circular dependency between Battle and Move classes.
 */

class MoveFactory {
 private:
  static std::vector<std::shared_ptr<Move>> createMoveMove( std::shared_ptr<Battle> battle );
  static std::vector<std::shared_ptr<Move>> createAttackMove( std::shared_ptr<Battle> battle );
 public:
  /**
   * @deprecated location of methods
   */
  static std::vector<std::shared_ptr<Move>> generateMoves( std::shared_ptr<Battle> battle );
};
