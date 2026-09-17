#pragma once

#include <variant>
#include <vector>

#include "core/Game/GameCommand.h"
#include "core/Game/GameContext.h"
#include "core/Game/UserCommand.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/Graphics/Visitor.h"
#include "core/Misc/Coords.h"
#include "aux/Overload.hpp"
#include "core/Misc/ProjectLib.h"

using NoTransition = std::monostate;
struct PopState {};
struct RequestBattle {
  int attacker_id_;
  int defender_id_;
  CoordPair at_;
  Terrain terrain_;
};

using StateTransition = std::variant<NoTransition, PopState, RequestBattle>;

class IGameState {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~IGameState() = default;

  template <typename RequiredUserCommandType>
  static bool isCommandForThisState( const UserCommand& command ) noexcept {
    return std::visit(
        Overload{ []( const RequiredUserCommandType& ) { return true; }, []( const auto& ) { return false; } },
        command );
  }
  template <typename RequiredGameCommandType>
  static bool isCommandForThisState( const GameCommand& command ) noexcept {
    return std::visit(
        Overload{ []( const RequiredGameCommandType& ) { return true; }, []( const auto& ) { return false; } },
        command );
  }

  [[nodiscard]] virtual std::vector<UserCommand> legalCommands() const noexcept = 0;
  [[nodiscard]] virtual StateTransition applyCommand( const UserCommand&, GameContext& ) noexcept = 0;
  [[nodiscard]] virtual bool isLegalCommand( const UserCommand& ) const noexcept = 0;

  virtual void applyGameCommand( const GameCommand&, GameContext& ) noexcept = 0;

  virtual void accept( IRVisitor& v ) const noexcept = 0;
};