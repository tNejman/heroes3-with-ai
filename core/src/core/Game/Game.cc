#include "core/Game/Game.h"

#include <cassert>
#include <format>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>

#include "aux/Err.hpp"
#include "aux/Overload.hpp"
#include "core/Algorithms/MinimaxAI.h"
#include "core/Battle/Battle.h"
#include "core/Character/Character.h"
#include "core/Exceptions/UnknownStateException.hpp"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/StateBattle.h"  // IWYU pragma: keep
#include "core/Game/StateOverworld.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Player/Player.h"
#include "core/Unit/Faction.hpp"
#include "core/WorldMap/WorldMap.h"
#include "engine/Graphics/IRVisitor.h"

game::StateTransition Game::handleStateIndependentCommand( const StateIndependentCommand& command ) noexcept {
  return std::visit( Overload{ [&]( const SwitchCharacter& ) -> game::StateTransition {
                       context_.nextCharacter();
                       std::cout << "switching hero. Now controlling: " << context_.getCurrentCharacter().getName()
                                 << ", at x=" << context_.getCurrentCharacter().getCoords().x_
                                 << " y=" << context_.getCurrentCharacter().getCoords().y_ << std::endl;
                       return game::NoTransition{};
                     } },
                     command );
}

void Game::handleStateTransition( const game::StateTransition& transition ) noexcept {
  std::visit( Overload{
                  []( const game::NoTransition& ) {},
                  [&]( const game::PopState& ) {
                    this->getStateStack().pop();
                    removeCharactersWithNoUnits();
                  },
                  [&]( const game::RequestBattle& rb ) { startBattle( rb ); },
              },
              transition );
}

void Game::removeCharactersWithNoUnits() {
  // TODO fix
  for ( const auto& player : context_.getPlayers() ) {
    for ( auto it = player->getCharacters().begin(); it != player->getCharacters().end(); ++it ) {
      bool all_empty = true;
      for ( auto& unit : ( *it )->army().getParty() ) {
        if ( unit ) {
          all_empty = false;
        }
      }
      if ( all_empty ) {
        this->getStateStack().top().applySystemCommand( EraseTile{ ( *it )->getCoords() }, context_ );
        player->getCharacters().erase( it );
        break;
      }
    }
  }
}

void Game::placeCharactersOnWorldMap() noexcept {
  for ( const auto& player_ptr : context_.getPlayers() ) {
    for ( const auto& character_ptr : player_ptr->getCharacters() ) {
      this->getStateStack().top().applySystemCommand(
          PlaceCharacter{ .character_id_ = character_ptr->getId(), .destination_ = character_ptr->getCoords() },
          context_ );
    }
  }
}

void Game::startBattle( const game::RequestBattle& request ) {
  auto attacker = context_.findCharacterById( request.attacker_id_ );
  auto defender = context_.findCharacterById( request.defender_id_ );
  if ( attacker == nullptr ) {
    err::raise<UnknownStateException>( std::format( "attacker not found; id={}", request.attacker_id_ ) );
  }
  if ( defender == nullptr ) {
    err::raise<UnknownStateException>( std::format( "defender not found; id={}", request.defender_id_ ) );
  }
  this->getStateStack().push( std::make_unique<game::StateBattle>( attacker, defender, request.terrain_ ) );
}

/* === @PUBLIC === */

Game::Game( std::vector<std::shared_ptr<Player>>&& players ) noexcept
    : context_( std::move( players ) ), minimax_( std::make_shared<MinimaxAI>() ) {
  err::passCondOrAbort( context_.getPlayers().size() >= 2, "at least 2 players needed to play" );
  this->getStateStack().push( game::StateOverworld::createUniqueptr() );
  this->placeCharactersOnWorldMap();
}

/* === COMMAND === */

[[nodiscard]] std::vector<UserCommand> Game::legalCommands() const noexcept {
  return this->getStateStack().top().legalCommands();
}
void Game::applyCommand( const UserCommand& command ) {
  incrementTickSinceStart();

  game::StateTransition transition = [&]() -> game::StateTransition {
    if ( const auto* state_indep_command = std::get_if<StateIndependentCommand>( &command ) ) {
      return handleStateIndependentCommand( *state_indep_command );
    }
    return this->getStateStack().top().applyCommand( command, context_ );
  }();
  handleStateTransition( transition );
}
[[nodiscard]] bool Game::isLegalCommand( const UserCommand& command ) const noexcept {
  return this->getStateStack().top().isLegalCommand( command );
}

/* === END COMMMAND === */

[[nodiscard]] const game::Context& Game::getContext() const noexcept {
  return context_;
}