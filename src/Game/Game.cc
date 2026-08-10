#include "Game/Game.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <cassert>
#include <format>
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
#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Game/GameCommand.h"
#include "Game/GameStateBattle.h"
#include "Game/GameStateOverworld.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Overload.hpp"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

// void Game::performGameLoopIterationOverworld( const UserCommand& command ) {
//   bool is_overworld_command = std::visit(
//       Overload{ []( const WorldMapCommand& ) { return true; }, []( const auto& ) { return false; } }, command );
//   CharacterMoveDirection move_direction = CharacterMoveDirection::NONE;
//   if ( is_overworld_command ) {
//     std::visit( Overload{ [&]( const MoveCharacter& mc ) { move_direction = mc.direction; },
//                           [&]( const EndTurn& ) { return; } },
//                 std::get<WorldMapCommand>( command ) );
//   }

//   if ( move_direction == CharacterMoveDirection::NONE ) {
//     return;
//   }

//   CoordPair center_coords = getMainCharacter()->getCoords();
//   try {
//     world_map_.moveMapObject( center_coords, WORLD_MAP_DIRECTIONS.at( static_cast<size_t>( move_direction ) ) );
//     center_coords = getMainCharacter()->getCoords();
//     getMainCharacter()->setOrientation( move_direction );
//   } catch ( const CoordinateOutOfBoundsException& e ) {
//     std::cout << e.what() << '\n';
//   } catch ( const InvalidMapMoveException& e ) {
//     try {
//       auto player_coords = getMainCharacter()->getCoords();
//       CoordPair new_coords =
//           player_coords + WORLD_MAP_DIRECTIONS.at( (size_t)move_direction );  // exception caught earlier, this is
//           safe
//       auto new_tile_obj = world_map_.getTile( new_coords )->getMapObject();
//       if ( new_tile_obj != nullptr ) {
//         if ( auto character_ptr = std::dynamic_pointer_cast<Character>( new_tile_obj ) ) {
//           startBattle( players_[0]->getCharacters()[0], character_ptr, world_map_.getTile( new_coords ) );
//         }
//       }
//       std::cout << e.what() << '\n';
//     } catch ( const std::exception& start_battle_failed_exception ) {
//       std::cout << "Game::_performGameLoopIterationOverworld() failed to start battle"
//                 << start_battle_failed_exception.what() << '\n';
//     }
//   }
// }

// void Game::performGameLoopIterationBattle( const UserCommand& command ) {
//   if ( battle_->getAttackingArmy().size() == 0 || battle_->getDefendingArmy().size() == 0
//        || battle_->getState() == BattleState::WIN_ATTACKER || battle_->getState() == BattleState::WIN_ATTACKER ) {
//     game_state_ = GameState::OVERWORLD;
//     battle_.reset();
//     removeCharactersWithNoUnits();
//     return;
//   }
//   auto moves = MoveFactory::generateMoves( battle_ );

//   if ( battle_->isAIMove() ) {
//     performBattleAiMove();
//   } else {
//     performBattleUserMove( command );
//   }
// }

// void Game::performBattleAiMove() {
//   auto moves = MoveFactory::generateMoves( battle_ );
//   std::shared_ptr<Move> best_move = nullptr;
//   for ( auto& move : moves ) {
//     if ( auto move_atk = std::dynamic_pointer_cast<AttackMove>( move ) ) {
//       best_move = move;
//       break;
//     }
//   }
//   // if ( best_move == nullptr ) best_move = minimax_->getBestMove( battle_, MINIMAX_MAX_DEPTH );
//   if ( best_move == nullptr ) {
//     best_move = moves[0];
//   }
//   best_move->execute( battle_ );
// }

// void Game::performBattleUserMove( const UserCommand& command ) {
//   auto moves = MoveFactory::generateMoves( *battle_ );
//   bool is_battle_command = std::visit(
//       Overload{ []( const BattleCommand& ) { return true; }, []( const auto& ) { return false; } }, command );
//   if ( !is_battle_command ) {
//     return;
//   }
//   std::optional<CoordPair> battle_coords = std::visit(
//       Overload{ []( const MoveStack& ms ) -> std::optional<CoordPair> { return CoordPair{ ms.destination }; },
//                 []( const AttackStack& as ) -> std::optional<CoordPair> { return CoordPair{ as.destination }; },
//                 []( const Wait& ) -> std::optional<CoordPair> { return std::nullopt; },
//                 []( const Defend& ) -> std::optional<CoordPair> { return std::nullopt; } },
//       std::get<BattleCommand>( command ) );
//   auto it = std::ranges::find_if(
//       moves, [&]( const std::shared_ptr<Move>& move ) { return move->destinationCoords() == battle_coords.value(); }
//       );

//   if ( it != moves.end() ) {
//     std::cout << "DEBUG: executing: " << ( *it )->getInfo( battle_ ) << '\n';
//     ( *it )->execute( battle_ );
//     waiting_for_print_ = true;
//   }
// }

void Game::removeCharactersWithNoUnits() {
  // TODO
  for ( auto& player : context_.getPlayers() ) {
    for ( auto it = player->getCharacters().begin(); it != player->getCharacters().end(); ++it ) {
      bool all_empty = true;
      for ( auto& unit : ( *it )->army().getParty() ) {
        if ( unit ) {
          all_empty = false;
        }
      }
      if ( all_empty ) {
        // world_map_.setMapObject( ( *it )->getCoords(), nullptr );
        state_stack_.top().applyGameCommand( EraseTile{ ( *it )->getCoords() }, context_ );
        player->getCharacters().erase( it );
        break;
      }
    }
  }
}

void Game::placeCharactersOnWorldMap() {
  for ( const auto& player_ptr : context_.getPlayers() ) {
    for ( const auto& character_ptr : player_ptr->getCharacters() ) {
      state_stack_.top().applyGameCommand(
          PlaceCharacter{ .character_id_ = character_ptr->getId(), .destination_ = character_ptr->getCoords() },
          context_ );
    }
  }
}

// @Deprecated
// void Game::startBattle( std::shared_ptr<Character> attacker, std::shared_ptr<Character> defender,
//                         std::shared_ptr<GridTile> background ) {
//   battle_ = std::make_shared<Battle>( attacker, defender, background );
//   game_state_ = GameState::BATTLE;
//   waiting_for_print_ = true;
// }

void Game::startBattle( const RequestBattle& request, std::shared_ptr<GridTile> background ) {
  auto attacker = context_.findCharacterById( request.attacker_id_ );
  auto defender = context_.findCharacterById( request.defender_id_ );
  if ( attacker == nullptr ) {
    err::raise<UnknownStateException>( std::format( "attacker not found; id={}", request.attacker_id_ ) );
  }
  if ( defender == nullptr ) {
    err::raise<UnknownStateException>( std::format( "defender not found; id={}", request.defender_id_ ) );
  }
  state_stack_.push( std::make_unique<GameStateBattle>( attacker, defender, background ) );
}

/* === @PUBLIC === */

Game::Game( std::vector<std::shared_ptr<Player>> players )
    : context_( std::move( players ) ), minimax_( std::make_shared<MinimaxAI>() ) {
  state_stack_.push( GameStateOverworld::createUniqueptr() );
  this->placeCharactersOnWorldMap();
}

/* === COMMAND === */
// [[nodiscard]] std::vector<UserCommand> Game::legalCommands() const noexcept {
// }
// void Game::applyCommand( const UserCommand& command );
// [[nodiscard]] bool Game::isLegalCommand( const UserCommand& command ) const noexcept;

/* === END COMMMAND === */

void Game::mapLoadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& obstacles ) {
  dynamic_cast<GameStateOverworld&>( state_stack_.top() ).loadObstacles( obstacles );  // TODO rewrite ASAP
}

void Game::performGameLoopIteration( const UserCommand& command ) {
  StateTransition transition = state_stack_.top().applyCommand( command, context_ );
  std::visit( Overload{
                  []( const NoTransition& ) {},
                  [&]( const PopState& ) { state_stack_.pop(); },
                  [&]( const RequestBattle& rb ) {
                    auto grid_tile = dynamic_cast<GameStateOverworld&>( state_stack_.top() )
                                         .viewMap()
                                         .getTile( rb.at_ );  // TODO rewrite ASAP
                    startBattle( rb, grid_tile );
                  },
              },
              transition );
  ++frames_since_start_;
}

std::shared_ptr<Character> Game::getMainCharacter() const {
  return context_.getPlayers()[0]->getCharacters()[0];
}

[[nodiscard]] int Game::getFrameCountSinceStart() const noexcept {
  return frames_since_start_;
}

[[nodiscard]] const IGameState& Game::getState() const noexcept {
  return state_stack_.top();
}
