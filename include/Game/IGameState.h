#pragma once

#include <variant>
#include <vector>

#include "Game/GameCommand.h"
#include "Game/GameContext.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Graphics/Visitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/Overload.hpp"
#include "Miscellaneous/ProjectLib.h"

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