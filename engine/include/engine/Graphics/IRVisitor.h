#pragma once

namespace game {

class StateOverworld;
class StateBattle;

}  // namespace game

class IRVisitor {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~IRVisitor() = default;

  virtual void visit( const game::StateOverworld& ) noexcept = 0;
  virtual void visit( const game::StateBattle& ) noexcept = 0;
};