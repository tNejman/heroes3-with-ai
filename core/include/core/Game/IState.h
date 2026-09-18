#pragma once

#include <variant>
#include <vector>

#include "aux/IsVariantMember.hpp"
#include "core/Game/Context.h"
#include "core/Game/SystemCommand.h"
#include "core/Game/UserCommand.h"
#include "core/Misc/ProjectLib.h"
#include "engine/Graphics/IRVisitor.h"
#include "engine/IGame/Coords.h"

namespace game {

using NoTransition = std::monostate;
struct PopState {};
struct RequestBattle {
  int attacker_id_;
  int defender_id_;
  CoordPair at_;
  Terrain terrain_;
};

using StateTransition = std::variant<NoTransition, PopState, RequestBattle>;

class IState {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~IState() = default;
  [[nodiscard]] virtual bool isCommandForThisState( const UserCommand& command ) const noexcept = 0;
  [[nodiscard]] virtual bool isCommandForThisState( const SystemCommand& command ) const noexcept = 0;

  [[nodiscard]] virtual std::vector<UserCommand> legalCommands() const noexcept = 0;
  [[nodiscard]] virtual StateTransition applyCommand( const UserCommand&, Context& ) noexcept = 0;
  [[nodiscard]] virtual bool isLegalCommand( const UserCommand& ) const noexcept = 0;

  virtual void applySystemCommand( const SystemCommand&, Context& ) noexcept = 0;

  virtual void accept( IRVisitor& v ) const noexcept = 0;
};

/* ==== ==== */

template <typename RequiredUserCommandType, typename RequiredSystemCommandType>
requires( IS_VARIANT_MEMBER_V<RequiredUserCommandType, UserCommand> )
        && (IS_VARIANT_MEMBER_V<RequiredSystemCommandType, SystemCommand>)
class StateOf : public IState {
 public:
  [[nodiscard]] bool isCommandForThisState( const UserCommand& command ) const noexcept final {
    return std::holds_alternative<RequiredUserCommandType>( command );
  }

  [[nodiscard]] bool isCommandForThisState( const SystemCommand& command ) const noexcept final {
    return std::holds_alternative<RequiredSystemCommandType>( command );
  }
};

}  // namespace game