

#include "Game/GameStateOverworld.h"

#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "Exceptions/Err.hpp"
#include "Exceptions/_NotImplementedException.hpp"
#include "Game/GameCommand.h"
#include "Game/GameContext.h"
#include "Game/IGameState.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "LoadAndSaveTools/MapLoader.h"
#include "Miscellaneous/Overload.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"

[[nodiscard]] GameStateOverworld GameStateOverworld::create() noexcept {
  return GameStateOverworld{ CtorKey{}, MapLoader{}.load( WORLD_MAP_INPUT_PATH ) };
}

[[nodiscard]] std::unique_ptr<IGameState> GameStateOverworld::createUniqueptr() noexcept {
  return std::make_unique<GameStateOverworld>( CtorKey{}, MapLoader{}.load( WORLD_MAP_INPUT_PATH ) );
}

// NOLINTNEXTLINE(readability-named-parameter)
GameStateOverworld::GameStateOverworld( CtorKey, WorldMap&& world_map ) noexcept : map_( std::move( world_map ) ) {
}

[[nodiscard]] std::vector<UserCommand> GameStateOverworld::legalCommands() const noexcept {
  err::raise<NotImplementedException>();
}

StateTransition GameStateOverworld::applyCommand( const UserCommand& command, GameContext& ) noexcept {
  if ( !isCommandForThisState<WorldMapCommand>( command ) ) {
    return NoTransition{};
  }
  return std::visit( Overload{ [&]( const MoveCharacter& mc ) -> StateTransition {
                                try {
                                  return map_.moveMapObject( mc.source_, mc.destination_ );
                                } catch ( const std::exception& e ) {
                                  std::cout << e.what() << '\n';
                                  return NoTransition{};
                                }
                              },
                               []( const auto& ) -> StateTransition { return NoTransition{}; } },
                     std::get<WorldMapCommand>( command ) );
}

[[nodiscard]] bool GameStateOverworld::isLegalCommand( const UserCommand& ) const noexcept {
  err::raise<NotImplementedException>();
}

void GameStateOverworld::applyGameCommand( const GameCommand& command, GameContext& context ) noexcept {
  if ( !isCommandForThisState<WorldMapGameCommand>( command ) ) {
    return;
  }
  std::visit( Overload{ [&]( const MoveMapObject& mmo ) { map_.moveMapObject( mmo.from_, mmo.to_ ); },
                        [&]( const EraseTile& et ) { map_.getTile( et.desitnation_ )->deleteObject(); },
                        [&]( const PlaceCharacter& pc ) {
                          auto character = context.findCharacterById( pc.character_id_ );
                          map_.getTile( pc.destination_ )->setMapObject( character );
                        } },
              std::get<WorldMapGameCommand>( command ) );
}

void GameStateOverworld::accept( IRVisitor& v ) const noexcept {
  v.visit( *this );
}

[[nodiscard]] const WorldMap& GameStateOverworld::viewMap() const noexcept {
  return map_;
}

void GameStateOverworld::loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& obstacles )  // TODO remove
{
  map_.loadObstacles( obstacles );
}
