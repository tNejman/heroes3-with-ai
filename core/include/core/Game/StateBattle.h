#pragma once

#include <memory>
#include <vector>

#include "core/Battle/Battle.h"
#include "core/Game/Context.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.hpp"
#include "core/Misc/ProjectLib.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/IGame/IState.h"

namespace game {

// class StateBattle : public game::StateOf<BattleCommand, BattleSystemCommand> {
class StateBattle : public IState {
 private:
  Battle battle_;

  [[nodiscard]] game::StateTransition handleMoveStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleAttackStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleWait() noexcept;
  // StateTransition handleDefend( const Defend & ) noexcept;

 public:
  StateBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background );

  [[nodiscard]] bool isCommandForThisState( const game::UserCommand &command ) const noexcept override;
  [[nodiscard]] bool isCommandForThisState( const SystemCommand &command ) const noexcept override;

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept override;
  [[nodiscard]] game::StateTransition applyCommand( const game::UserCommand &, game::Context & ) noexcept override;
  [[nodiscard]] bool isLegalCommand( const game::UserCommand & ) const noexcept override;

  void applySystemCommand( const SystemCommand &, game::Context & ) noexcept override;

  void accept( IRVisitor &v ) const noexcept override;

  const Battle &viewBattle() const noexcept;
};

}  // namespace game