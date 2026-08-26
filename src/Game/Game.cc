#include "Game/Game.h"

#include <cassert>
#include <format>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "Algorithms/MinimaxAI.h"
#include "Battle/Battle.h"
#include "Character/Character.h"
#include "Exceptions/Err.hpp"
#include "Exceptions/UnknownStateException.hpp"
#include "Game/GameCommand.h"
#include "Game/GameContext.h"
#include "Game/GameStateBattle.h"
#include "Game/GameStateOverworld.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/Overload.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "Player/Player.h"
#include "Unit/Faction.hpp"
#include "WorldMap/WorldMap.h"


void Game::handleStateTransition( const StateTransition& transition ) noexcept {
  std::visit( Overload{
                  []( const NoTransition& ) {},
                  [&]( const PopState& ) { state_stack_.pop(); },
                  [&]( const RequestBattle& rb ) {
                    auto terrain = dynamic_cast<GameStateOverworld&>( state_stack_.top() )
                                       .viewMap()
                                       .getTerrain( rb.at_ );  // TODO rewrite ASAP (dynamic cast bad)
                    startBattle( rb, terrain );
                  },
              },
              transition );
}

void Game::removeCharactersWithNoUnits() {
  // TODO fix
  for ( auto& player : context_.getPlayers() ) {
    for ( auto it = player->getCharacters().begin(); it != player->getCharacters().end(); ++it ) {
      bool all_empty = true;
      for ( auto& unit : ( *it )->army().getParty() ) {
        if ( unit ) {
          all_empty = false;
        }
      }
      if ( all_empty ) {
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

void Game::startBattle( const RequestBattle& request, Terrain background ) {
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

[[nodiscard]] std::vector<UserCommand> Game::legalCommands() const noexcept {
  return state_stack_.top().legalCommands();
}
void Game::applyCommand( const UserCommand& command ) {
  StateTransition transition = state_stack_.top().applyCommand( command, context_ );
  handleStateTransition( transition );
  ++frames_since_start_;
}
[[nodiscard]] bool Game::isLegalCommand( const UserCommand& command ) const noexcept {
  return state_stack_.top().isLegalCommand( command );
}

/* === END COMMMAND === */

std::shared_ptr<Character> Game::getMainCharacter() const {
  return context_.getPlayers()[0]->getCharacters()[0];
}

[[nodiscard]] int Game::getFrameCountSinceStart() const noexcept {
  return frames_since_start_;
}

[[nodiscard]] const IGameState& Game::getState() const noexcept {
  return state_stack_.top();
}

[[nodiscard]] const GameContext& Game::getContext() const noexcept {
  return context_;
}
