#pragma once

#include <memory>

#include "core/Game/StateBattle.h"
#include "core/Game/UserCommand.h"

struct CoordPair;
class Battle;
class UnitStack;

class IAlgorithm {
 private:
 public:
  IAlgorithm() = default;
  IAlgorithm( const IAlgorithm& ) = default;
  IAlgorithm& operator=( const IAlgorithm& ) = default;
  IAlgorithm( IAlgorithm&& ) noexcept = default;
  IAlgorithm& operator=( IAlgorithm&& ) noexcept = default;
  virtual ~IAlgorithm() = default;
  [[nodiscard]] virtual UserCommand getBestMove( std::reference_wrapper<game::StateBattle> state_battle ) = 0;
};