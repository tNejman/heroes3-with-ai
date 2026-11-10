#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "core/Battle/Battle.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Magic/Spell.h"
#include "core/Magic/SpellLib.h"
#include "core/Misc/ProjectLib.h"
#include "engine/model/IGraphics/IRVisitor.h"

namespace game {

constexpr inline std::nullopt_t NO_SPELL = std::nullopt;

class StateBattle : public game::StateOf<BattleCommand, BattleSystemCommand> {
 private:
  Battle battle_;

  [[nodiscard]] std::vector<BattleCommand> createMoveCommands() const noexcept;
  [[nodiscard]] std::vector<BattleCommand> createAttackCommands() const noexcept;
  [[nodiscard]] std::vector<BattleCommand> createWaitCommands() const noexcept;
  // [[nodiscard]] std::vector<BattleCommand> createDefendCommands() const noexcept;
  [[nodiscard]] std::vector<BattleCommand> createCastSpellCommands() const noexcept;

  [[nodiscard]] std::vector<std::reference_wrapper<UnitStack>> unitsOnSide( spell::Target::Side side ) const noexcept;
  [[nodiscard]] static std::vector<BattleCommand> commandsPerUnit(
      const Spell &spell, const std::vector<std::reference_wrapper<UnitStack>> &units ) noexcept;
  [[nodiscard]] std::vector<BattleCommand> commandsPerEmptyTile(
      BattleCommand::Action, std::optional<std::reference_wrapper<const Spell>> ) const noexcept;
  [[nodiscard]] std::vector<BattleCommand> commandsPerTile(
      BattleCommand::Action, std::optional<std::reference_wrapper<const Spell>> ) const noexcept;

  [[nodiscard]] std::vector<BattleCommand> createAoeSpellCommands( const Spell & ) const noexcept;

  [[nodiscard]] game::StateTransition handleMoveStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleAttackStack( const BattleCommand & ) noexcept;
  [[nodiscard]] game::StateTransition handleWait() noexcept;
  // StateTransition handleDefend( const Defend & ) noexcept;
  [[nodiscard]] game::StateTransition handleCastSpell( const BattleCommand & ) noexcept;

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