#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Game:
    - Klasa Game odpowiada za zarządzanie grą, w tym za mapę świata, graczy i frakcje.
    - Zawiera metody do inicjalizacji gry, dodawania graczy i frakcji oraz zarządzania rozgrywką.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Algorithms/MinimaxAI.h"
#include "Exceptions/UnknownStateException.hpp"
#include "Game/KeyHandler.h"
#include "Graphic/Renderers/MapRenderer.h"
#include "LoadAndSaveTools/MapLoader.h"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Units/Faction.hpp"
#include "WorldMap/WorldMap.h"

class Game {
 private:
  GameState game_state_ = GameState::OVERWORLD;
  std::shared_ptr<WorldMap> world_map_;

  // players_[0] should be the main player
  std::vector<std::shared_ptr<Player>> players_;
  std::vector<std::shared_ptr<Faction>> factions_;
  std::shared_ptr<Battle> battle_;

  std::shared_ptr<sf::RenderWindow> render_window_;
  std::shared_ptr<SpriteVisitor> sprite_visitor_;
  std::shared_ptr<MapRenderer> map_renderer_;
  std::shared_ptr<KeyHandler> key_handler_;
  std::shared_ptr<MinimaxAI> minimax_;

  // std::optional<sf::Event> event_ = std::nullopt;
  int mouse_x_ = 0;
  int mouse_y_ = 0;
  bool waiting_for_print_ = true;
  int is_player_turn_counter = 0;

  void _performGameLoopIterationOverworld();
  void _performGameLoopIterationBattle();

  void _performBattleAIMove();
  void _performBattleUserMove();

  void placeCharactersOnWorldMap();
  bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const;
  std::optional<CoordPair> getCoordsFromClick();
  void startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender, std::shared_ptr<GridTile> background );

 public:
  Game( std::vector<std::shared_ptr<Player>> players );
  Game( std::vector<std::shared_ptr<Player>> players, bool if_buffered_input );
  // TODO add to constructor functionality which initializes preset players

  void loadObstacles( std::vector<std::shared_ptr<MapObject>>& obstacles );
  GameState getState() const;
  void setMouseCoords( int x, int y );
  void performGameLoopIteration();
  CoordPair getMainPlayerCoords() const;
  std::shared_ptr<sf::RenderWindow> getRenderWindow();
  void debugStartBattle();
};