#pragma once

#include <memory>
#include <vector>

#include "Battle/Battle.h"
#include "Game/GameCommand.h"
#include "Game/GameContext.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/ProjectLib.h"

class GameStateBattle : public IGameState {
 private:
  Battle battle_;

  [[nodiscard]] StateTransition handleMoveStack( const BattleCommand & ) noexcept;
  [[nodiscard]] StateTransition handleAttackStack( const BattleCommand & ) noexcept;
  [[nodiscard]] StateTransition handleWait() noexcept;
  // StateTransition handleDefend( const Defend & ) noexcept;

 public:
  GameStateBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, Terrain background );

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept override;
  [[nodiscard]] StateTransition applyCommand( const UserCommand &, GameContext & ) noexcept override;
  [[nodiscard]] bool isLegalCommand( const UserCommand & ) const noexcept override;

  void applyGameCommand( const GameCommand &, GameContext & ) noexcept override;

  void accept( IRVisitor &v ) const noexcept override;

  const Battle &viewBattle() const noexcept;
};