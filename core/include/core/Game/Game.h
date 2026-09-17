#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Game:
    - Klasa Game odpowiada za zarządzanie grą, w tym za mapę świata, graczy i frakcje.
    - Zawiera metody do inicjalizacji gry, dodawania graczy i frakcji oraz zarządzania rozgrywką.
*/

#include <memory>
#include <vector>

#include "core/Algorithms/MinimaxAI.h"
#include "core/Game/GameContext.h"
#include "core/Game/GameStateStack.h"
#include "core/Game/IGameState.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "core/WorldMap/WorldMap.h"

class Game {
 private:
  GameStateStack state_stack_;
  GameContext context_;

  std::shared_ptr<MinimaxAI> minimax_;

  int frames_since_start_ = 0;

  StateTransition handleStateIndependentCommand( const StateIndependentCommand& ) noexcept;
  void handleStateTransition( const StateTransition& ) noexcept;

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap();
  void startBattle( const RequestBattle& request );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  // TODO add to constructor functionality which initializes preset players

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept;
  void applyCommand( const UserCommand& command );
  [[nodiscard]] bool isLegalCommand( const UserCommand& command ) const noexcept;

  [[nodiscard]] int getFrameCountSinceStart() const noexcept;

  [[nodiscard]] const IGameState& getState() const noexcept;
  [[nodiscard]] const GameContext& getContext() const noexcept;
};