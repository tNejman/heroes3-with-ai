#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Game:
    - Klasa Game odpowiada za zarządzanie grą, w tym za mapę świata, graczy i frakcje.
    - Zawiera metody do inicjalizacji gry, dodawania graczy i frakcji oraz zarządzania rozgrywką.
*/

#include <memory>
#include <vector>

#include "core/Algorithms/MinimaxAI.h"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/UserCommand.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "engine/IGame/IGame.h"

class Game : public game::IGame {
 private:
  game::Context context_;

  std::shared_ptr<MinimaxAI> minimax_;

  game::StateTransition handleStateIndependentCommand( const StateIndependentCommand& ) noexcept;
  void handleStateTransition( const game::StateTransition& ) noexcept;

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap() noexcept;
  void startBattle( const game::RequestBattle& request );

 public:
  Game( std::vector<std::shared_ptr<Player>>&& players ) noexcept;
  // TODO add to constructor functionality which initializes preset players

  [[nodiscard]] std::vector<UserCommand> legalCommands() const noexcept;
  void applyCommand( const UserCommand& command );
  [[nodiscard]] bool isLegalCommand( const UserCommand& command ) const noexcept;

  [[nodiscard]] const game::Context& getContext() const noexcept;
};