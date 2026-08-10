#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Game:
    - Klasa Game odpowiada za zarządzanie grą, w tym za mapę świata, graczy i frakcje.
    - Zawiera metody do inicjalizacji gry, dodawania graczy i frakcji oraz zarządzania rozgrywką.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <vector>

#include "Algorithms/MinimaxAI.h"
#include "Game/GameContext.h"
#include "Game/GameStateStack.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

class Game {
 private:
  GameStateStack state_stack_;
  GameContext context_;

  std::shared_ptr<MinimaxAI> minimax_;

  bool waiting_for_print_ = true;
  int frames_since_start_ = 0;

  void performGameLoopIterationOverworld( const UserCommand& command );
  void performGameLoopIterationBattle( const UserCommand& command );

//   void performBattleAiMove();
//   void performBattleUserMove( const UserCommand& command );

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap();
  void startBattle( const RequestBattle& request, std::shared_ptr<GridTile> background );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  // TODO add to constructor functionality which initializes preset players

  void mapLoadObstacles(
      std::vector<std::shared_ptr<OverworldObstacle>>& obstacles );  // TODO expose map rather than proxy methods
  void performGameLoopIteration( const UserCommand& command );
  [[nodiscard]] std::shared_ptr<Character> getMainCharacter() const;

  [[nodiscard]] int getFrameCountSinceStart() const noexcept;

  [[nodiscard]] const IGameState& getState() const noexcept;
};