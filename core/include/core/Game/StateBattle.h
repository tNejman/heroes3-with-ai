#pragma once

#include <memory>
#include <vector>

#include "core/Battle/Battle.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "engine/Graphics/IRVisitor.h"

namespace game {

class StateBattle : public game::StateOf<BattleCommand, BattleSystemCommand> {
 private:
  Battle battle_;

  [[nodiscard]] game::StateTransition handleMoveStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleAttackStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleWait() noexcept;
  // StateTransition handleDefend( const Defend & ) noexcept;

 public:
  StateBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background );

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept override;
  [[nodiscard]] game::StateTransition applyCommand( const UserCommand &, game::Context & ) noexcept override;
  [[nodiscard]] bool isLegalCommand( const UserCommand & ) const noexcept override;

  void applySystemCommand( const SystemCommand &, game::Context & ) noexcept override;

  void accept( IRVisitor &v ) const noexcept override;

  const Battle &viewBattle() const noexcept;
};

}  // namespace game