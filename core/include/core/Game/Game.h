#pragma once

#include <memory>
#include <vector>

#include "engine/model/IGame/IGame.h"

#include "core/Algorithms/MinimaxAI.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/UserCommand.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "core/WorldMap/WorldMap.h"

class Game : public game::IGame {
 private:
  game::Context context_;

  std::shared_ptr<MinimaxAI> minimax_;

  [[nodiscard]] game::StateTransition handleStateIndependentCommand( const StateIndependentCommand& ) noexcept;
  void handleStateTransition( const game::StateTransition& ) noexcept;

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap() noexcept;
  void startBattle( const game::RequestBattle& request );

 public:
  [[nodiscard]] Game( std::vector<std::shared_ptr<Player>>&& players, WorldMap&& ) noexcept;
  // TODO add to constructor functionality which initializes preset players

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept;
  void applyCommand( const UserCommand& command ) noexcept;
  [[nodiscard]] bool isLegalCommand( const UserCommand& command ) const noexcept;

  [[nodiscard]] const game::Context& getContext() const noexcept;
};