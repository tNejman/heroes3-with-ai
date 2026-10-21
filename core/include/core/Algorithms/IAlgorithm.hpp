#pragma once

#include <memory>
#include "core/Game/UserCommand.h"

class Move;
struct CoordPair;
class Battle;
class UnitStack;



class IAlgorithm {
 private:

 public:
  IAlgorithm() = default;
  IAlgorithm(const IAlgorithm&) = default;
  IAlgorithm& operator=(const IAlgorithm&) = default;
  IAlgorithm(IAlgorithm&&) noexcept = default;
  IAlgorithm& operator=(IAlgorithm&&) noexcept = default;
  virtual ~IAlgorithm() = default;
  [[nodiscard]] virtual std::shared_ptr<Move> getBestMove( std::shared_ptr<Battle> battle) = 0;
};