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
#include "Game/KeyboardHandler.h"
#include "Game/UserCommand.h"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

class Game {
 private:
  GameState game_state_ = GameState::OVERWORLD;
  WorldMap world_map_;

  // players_[0] should be the main player
  std::vector<std::shared_ptr<Player>> players_;
  //   std::vector<std::shared_ptr<Faction>> factions_;
  std::shared_ptr<Battle> battle_;

  std::shared_ptr<MinimaxAI> minimax_;

  // std::optional<sf::Event> event_ = std::nullopt;
  bool waiting_for_print_ = true;
  int frames_since_start_ = 0;
  //   int is_player_turn_counter_ = 0;

  void performGameLoopIterationOverworld( const UserCommand& command );
  void performGameLoopIterationBattle( const UserCommand& command );

  void performBattleAiMove();
  void performBattleUserMove( const UserCommand& command );

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap();
  void startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                    std::shared_ptr<GridTile> background );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  // TODO add to constructor functionality which initializes preset players

  void mapLoadObstacles(
      std::vector<std::shared_ptr<OverworldObstacle>>& obstacles );  // TODO expose map rather than proxy methods
  [[nodiscard]] GameState getState() const;
  void performGameLoopIteration( const UserCommand& command );
  [[nodiscard]] std::shared_ptr<Character> getMainCharacter() const;
  void debugStartBattle();
  [[nodiscard]] int getFrameCountSinceStart() const noexcept;

  [[nodiscard]] const WorldMap& getMap() const noexcept;
  [[nodiscard]] const Battle& getBattle() const noexcept;
};