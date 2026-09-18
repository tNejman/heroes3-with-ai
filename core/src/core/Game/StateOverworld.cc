

#include "core/Game/StateOverworld.h"

#include <cassert>
#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <variant>
#include <vector>

#include "aux/DiscardReturn.hpp"
#include "aux/Err.hpp"
#include "aux/Overload.hpp"
#include "aux/_NotImplementedException.hpp"
#include "core/Game/Context.h"
#include "core/Game/IState.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "core/WorldMap/OverworldObstacle.h"
#include "core/WorldMap/WorldMap.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/LoadAndSaveTools/MapLoader.h"

/* ==== @PUBLIC ==== */

// NOLINTNEXTLINE(readability-named-parameter)
game::StateOverworld::StateOverworld( CtorKey, WorldMap&& world_map ) noexcept : map_( std::move( world_map ) ) {
}

[[nodiscard]] game::StateOverworld game::StateOverworld::create() noexcept {
  return game::StateOverworld{ CtorKey{}, MapLoader{}.load( WORLD_MAP_INPUT_PATH ) };
}

[[nodiscard]] std::unique_ptr<game::IState> game::StateOverworld::createUniqueptr() noexcept {
  return std::make_unique<game::StateOverworld>( CtorKey{}, MapLoader{}.load( WORLD_MAP_INPUT_PATH ) );
}

[[nodiscard]] std::vector<UserCommand> game::StateOverworld::legalCommands() const noexcept {
  err::raise<NotImplementedException>();
}

game::StateTransition game::StateOverworld::applyCommand( const UserCommand& command, game::Context& ) noexcept {
  if ( !isCommandForThisState( command ) ) {
    return game::NoTransition{};
  }
  return std::visit( Overload{ [&]( const MoveCharacter& mc ) -> game::StateTransition {
                                try {
                                  return map_.moveMapObject( mc.source_, mc.destination_ );
                                } catch ( const std::exception& e ) {
                                  std::cout << e.what() << '\n';
                                  return game::NoTransition{};
                                }
                              },
                               []( const auto& ) -> game::StateTransition { return game::NoTransition{}; } },
                     std::get<WorldMapCommand>( command ) );
}

[[nodiscard]] bool game::StateOverworld::isLegalCommand( const UserCommand& ) const noexcept {
  err::raise<NotImplementedException>();
}

void game::StateOverworld::applySystemCommand( const SystemCommand& command, game::Context& context ) noexcept {
  if ( !isCommandForThisState( command ) ) {
    return;
  }
  // game command is to apply the state transition not recieve it
  std::visit( Overload{ [&]( const MoveMapObject& mmo ) {
                         DISCARD_RETURN()
                         map_.moveMapObject( mmo.from_, mmo.to_ );
                       },
                        [&]( const EraseTile& et ) { map_.resetMapObject( et.desitnation_ ); },
                        [&]( const PlaceCharacter& pc ) {
                          auto character = context.findCharacterById( pc.character_id_ );
                          map_.setMapObject( pc.destination_, std::move( character ) );
                        } },
              std::get<WorldMapSystemCommand>( command ) );
}

void game::StateOverworld::accept( IRVisitor& v ) const noexcept {
  v.visit( *this );
}

[[nodiscard]] const WorldMap& game::StateOverworld::viewMap() const noexcept {
  return map_;
}
