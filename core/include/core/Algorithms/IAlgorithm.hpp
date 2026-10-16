#pragma once

#include <cstdint>
#include <memory>
#include <utility>
#include <vector>
#include "core/Game/UserCommand.h"

class Move;
struct CoordPair;
class Battle;
class UnitStack;



class IAlgorithm {
 private:

 public:
  IAlgorithm() = default;
  virtual ~IAlgorithm() = default;
  [[nodiscard]] std::shared_ptr<UserCommand> getBestMove( std::shared_ptr<Battle> battle);
};