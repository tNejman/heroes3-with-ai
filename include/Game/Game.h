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
#include <optional>
#include <vector>

#include "Algorithms/MinimaxAI.h"
#include "Game/GameStateStack.h"
#include "Game/KeyboardHandler.h"
#include "Graphics/Renderers/MapRenderer.h"
#include "Graphics/SpriteVisitor.h"
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

  std::shared_ptr<KeyHandler> key_handler_;
  std::shared_ptr<MinimaxAI> minimax_;

  // std::optional<sf::Event> event_ = std::nullopt;
  int mouse_x_ = 0;
  int mouse_y_ = 0;
  bool waiting_for_print_ = true;
  int frames_since_start_ = 0;
  //   int is_player_turn_counter_ = 0;

  void performGameLoopIterationOverworld();
  void performGameLoopIterationBattle();

  void performBattleAiMove();
  void performBattleUserMove();

  void removeCharactersWithNoUnits();

  void placeCharactersOnWorldMap();
  [[nodiscard]] bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const;
  std::optional<CoordPair> getCoordsFromClick();
  void startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                    std::shared_ptr<GridTile> background );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  Game( std::vector<std::shared_ptr<Player>> players, bool if_buffered_input );
  // TODO add to constructor functionality which initializes preset players

  void mapLoadObstacles(
      std::vector<std::shared_ptr<OverworldObstacle>>& obstacles );  // TODO expose map rather than proxy methods
  [[nodiscard]] GameState getState() const;
  void setMouseCoords( int x, int y );  // NOLINT(readability-identifier-length)
  void performGameLoopIteration();
  [[nodiscard]] std::shared_ptr<Character> getMainCharacter() const;
  void debugStartBattle();
  [[nodiscard]] int getFrameCountSinceStart() const noexcept;

  [[nodiscard]] const WorldMap& getMap() const noexcept;
  [[nodiscard]] const Battle& getBattle() const noexcept;
};