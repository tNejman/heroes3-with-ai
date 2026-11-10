#pragma once

#include <magic_enum/magic_enum.hpp>
#include <sstream>
#include <string>
#include <variant>

#include "core/Character/Character.h"
#include "core/Game/UserCommand.h"
#include "engine/model/IGame/Coords.h"

inline std::string toString( const CoordPair& cp ) {
  return "x=" + std::to_string( cp.x_ ) + ", y=" + std::to_string( cp.y_ );
}

inline std::string toString( const Character& character ) {
  return std::string{ "Character<name=" + character.getName() + ", id=" + std::to_string( character.getId() ) + ">" };
}

inline std::string toString( const UserCommand& command ) {
  if ( !std::holds_alternative<BattleCommand>( command ) ) {
    return "nu uh";
  }

  const auto battle_command = std::get<BattleCommand>( command );
  std::stringstream msg;
  msg << "BattleCommand{action =" << magic_enum::enum_name( battle_command.action_ )
      << ", spell?= " << battle_command.maybe_spell_.has_value()
      << ", destination= " << toString( battle_command.destination_ ) << "}";

  return msg.str();
}