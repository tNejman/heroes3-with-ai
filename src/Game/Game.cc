#include "Game/Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <utility>
#include <variant>
#include <vector>

#include "Algorithms/MinimaxAI.h"
#include "Battle/Battle.h"
#include "Battle/Moves/AttackMove.h"
#include "Battle/Moves/Move.hpp"
#include "Battle/Moves/MoveFactory.h"
#include "Character/Character.h"
#include "Exceptions/CoordinateOutOfBoundsException.hpp"
#include "Exceptions/Err.hpp"
#include "Exceptions/InvalidMapMoveException.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Game/KeyboardHandler.h"
#include "Game/UserCommand.h"
#include "LoadAndSaveTools/MapLoader.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Overload.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

void Game::performGameLoopIterationOverworld( const UserCommand& command ) {
  bool is_overworld_command = std::visit(
      Overload{ []( const WorldMapCommand& ) { return true; }, []( const auto& ) { return false; } }, command );
  CharacterMoveDirection move_direction = CharacterMoveDirection::NONE;
  if ( is_overworld_command ) {
    std::visit( Overload{ [&]( const MoveCharacter& mc ) { move_direction = mc.direction; },
                          [&]( const EndTurn& ) { return; } },
                std::get<WorldMapCommand>( command ) );
  }

  CoordPair center_coords = getMainCharacter()->getCoords();
  if ( move_direction != CharacterMoveDirection::NONE ) {
    try {
      world_map_.moveMapObject( getMainCharacter()->getCoords(), WORLD_MAP_DIRECTIONS.at( (size_t)move_direction ) );
      center_coords = getMainCharacter()->getCoords();
      getMainCharacter()->setOrientation( move_direction );
    } catch ( const CoordinateOutOfBoundsException& e ) {
      std::cout << e.what() << '\n';
    } catch ( const InvalidMapMoveException& e ) {
      try {
        auto player_coords = getMainCharacter()->getCoords();
        CoordPair new_coords =
            player_coords
            + WORLD_MAP_DIRECTIONS.at( (size_t)move_direction );  // exception caught earlier, this is safe
        auto new_tile_obj = world_map_.getTile( new_coords )->getMapObject();
        if ( new_tile_obj != nullptr ) {
          if ( auto character_ptr = std::dynamic_pointer_cast<Character>( new_tile_obj ) ) {
            startBattle( players_[0]->getCharacters()[0], character_ptr, world_map_.getTile( new_coords ) );
          }
        }
        std::cout << e.what() << '\n';
      } catch ( const std::exception& start_battle_failed_exception ) {
        std::cout << "Game::_performGameLoopIterationOverworld() failed to start battle"
                  << start_battle_failed_exception.what() << '\n';
      }
    }
  }
}

void Game::performGameLoopIterationBattle( const UserCommand& command ) {
  if ( battle_->getAttackingArmy().size() == 0 || battle_->getDefendingArmy().size() == 0
       || battle_->getState() == BattleState::WIN_ATTACKER || battle_->getState() == BattleState::WIN_ATTACKER ) {
    game_state_ = GameState::OVERWORLD;
    battle_.reset();
    removeCharactersWithNoUnits();
    return;
  }
  auto moves = MoveFactory::generateMoves( battle_ );

  if ( battle_->isAIMove() ) {
    performBattleAiMove();
  } else {
    performBattleUserMove( command );
  }
}

void Game::performBattleAiMove() {
  auto moves = MoveFactory::generateMoves( battle_ );
  std::shared_ptr<Move> best_move = nullptr;
  for ( auto& move : moves ) {
    if ( auto move_atk = std::dynamic_pointer_cast<AttackMove>( move ) ) {
      best_move = move;
      break;
    }
  }
  // if ( best_move == nullptr ) best_move = minimax_->getBestMove( battle_, MINIMAX_MAX_DEPTH );
  if ( best_move == nullptr ) {
    best_move = moves[0];
  }
  best_move->execute( battle_ );
}

void Game::performBattleUserMove( const UserCommand& command ) {
  auto moves = MoveFactory::generateMoves( battle_ );
  bool is_battle_command = std::visit(
      Overload{ []( const BattleCommand& ) { return true; }, []( const auto& ) { return false; } }, command );
  if ( !is_battle_command ) {
    return;
  }
  std::optional<CoordPair> battle_coords = std::visit(
      Overload{ []( const MoveStack& ms ) -> std::optional<CoordPair> { return CoordPair{ ms.destination }; },
                []( const AttackStack& as ) -> std::optional<CoordPair> { return CoordPair{ as.destination }; },
                []( const Wait& ) -> std::optional<CoordPair> { return std::nullopt; },
                []( const Defend& ) -> std::optional<CoordPair> { return std::nullopt; } },
      std::get<BattleCommand>( command ) );
  auto it = std::ranges::find_if(
      moves, [&]( const std::shared_ptr<Move>& move ) { return move->destinationCoords() == battle_coords.value(); } );

  if ( it != moves.end() ) {
    std::cout << "DEBUG: executing: " << ( *it )->getInfo( battle_ ) << '\n';
    ( *it )->execute( battle_ );
    waiting_for_print_ = true;
  }
}

void Game::removeCharactersWithNoUnits() {
  // TODO
  for ( auto& player : players_ ) {
    for ( auto it = player->getCharacters().begin(); it != player->getCharacters().end(); ++it ) {
      bool all_empty = true;
      for ( auto& unit : ( *it )->army().getParty() ) {
        if ( unit ) {
          all_empty = false;
        }
      }
      if ( all_empty ) {
        world_map_.setMapObject( ( *it )->getCoords(), nullptr );
        player->getCharacters().erase( it );
        break;
      }
    }
  }
}

void Game::placeCharactersOnWorldMap() {
  // const auto& main_character_ptr = players_[0]->getCharacters()[0];
  // world_map_->setMapObject( CoordPair( 0u, 0u ), character_ptr );
  for ( const auto& player_ptr : players_ ) {
    for ( const auto& character_ptr : player_ptr->getCharacters() ) {
      CoordPair character_coords = character_ptr->getCoords();
      world_map_.setMapObject( character_coords, character_ptr );
    }
  }
}

void Game::startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
                        std::shared_ptr<GridTile> background ) {
  battle_ = std::make_shared<Battle>( attacker, defender, background );
  game_state_ = GameState::BATTLE;
  waiting_for_print_ = true;
}

Game::Game( std::vector<std::shared_ptr<Player>> players )
    : world_map_( MapLoader{}.load( WORLD_MAP_INPUT_PATH ) ),
      players_( std::move( players ) ),
      // factions_( { std::make_shared<FactionForge>(), std::make_shared<FactionConflux>() } ),
      minimax_( std::make_shared<MinimaxAI>() ) {
  this->placeCharactersOnWorldMap();
}

/* === COMMAND === */
// [[nodiscard]] std::vector<UserCommand> Game::legalCommands() const noexcept {
// }
// void Game::applyCommand( const UserCommand& command );
// [[nodiscard]] bool Game::isLegalCommand( const UserCommand& command ) const noexcept;

/* === END COMMMAND === */

void Game::mapLoadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& obstacles ) {
  world_map_.loadObstacles( obstacles );
}

GameState Game::getState() const {
  return game_state_;
}

void Game::performGameLoopIteration( const UserCommand& command ) {
  switch ( game_state_ ) {
    case GameState::OVERWORLD: performGameLoopIterationOverworld( command ); break;
    case GameState::BATTLE: performGameLoopIterationBattle( command ); break;
    default: err::raise<UnknownStateException>( "tried to perform action regarding forbidden game state" );
  }
  ++frames_since_start_;
}

std::shared_ptr<Character> Game::getMainCharacter() const {
  return players_[0]->getCharacters()[0];
}

void Game::debugStartBattle() {
  battle_ = std::make_shared<Battle>( players_[0]->getCharacters()[0], players_[1]->getCharacters()[0],
                                      world_map_.getTile( { 0, 0 } ) );
  game_state_ = GameState::BATTLE;
  waiting_for_print_ = true;
}

[[nodiscard]] int Game::getFrameCountSinceStart() const noexcept {
  return frames_since_start_;
}

[[nodiscard]] const WorldMap& Game::getMap() const noexcept {
  return world_map_;
}

[[nodiscard]] const Battle& Game::getBattle() const noexcept {
  return *battle_;
}
