#pragma once

class GameStateOverworld;
class GameStateBattle;

class IRVisitor {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~IRVisitor() = default;

  virtual void visit( const GameStateOverworld& ) noexcept = 0;
  virtual void visit( const GameStateBattle& ) noexcept = 0;
};