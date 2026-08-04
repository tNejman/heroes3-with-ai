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
#include "Game/Command.h"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

class Game {
 private:
  GameState game_state_ = GameState::OVERWORLD;
  std::shared_ptr<WorldMap> world_map_;

  // players_[0] should be the main player
  std::vector<std::shared_ptr<Player>> players_;
  std::shared_ptr<Battle> battle_;

  std::shared_ptr<MinimaxAI> minimax_;

  // std::optional<sf::Event> event_ = std::nullopt;

  //   int is_player_turn_counter_ = 0;

  void performGameLoopIterationOverworld();
  void performGameLoopIterationBattle();

  void performBattleAiMove();
  void performBattleUserMove();

  void placeCharactersOnWorldMap();
  void startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                    std::shared_ptr<GridTile> background );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  Game( std::vector<std::shared_ptr<Player>> players, bool is_buffered );
  // TODO add to constructor functionality which initializes preset players

  [[nodiscard]] std::vector<Command> legalCommands() const noexcept;
  void applyCommand( const Command& command );
  [[nodiscard]] bool isLegalCommand( const Command& command ) const noexcept;

  void mapLoadObstacles(
      std::vector<std::shared_ptr<OverworldObstacle>>& obstacles );  // TODO expose map rather than proxy methods
  [[nodiscard]] GameState getState() const;
  [[nodiscard]] std::shared_ptr<Character> getMainCharacter() const;
  void debugStartBattle();
};