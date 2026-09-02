
#include "IO/MouseHandler.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <optional>

#include "Battle/Battle.h"
#include "Battle/Moves/AttackMove.h"
#include "Battle/Moves/Move.hpp"
#include "Battle/Moves/MoveMove.h"
#include "Battle/Moves/WaitMove.h"
#include "Exceptions/Err.hpp"
#include "Game/GameStateBattle.h"
#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"

[[nodiscard]] std::optional<CoordPair> MouseHandler::getHexagonCoordsFromClick( int mx, int my ) const noexcept {
  if ( mx < 0 || my < 0 ) {
    return std::nullopt;
  }

  for ( int x = 0; x < MAP_WIDTH_BF; ++x ) {
    for ( int y = 0; y < MAP_HEIGHT_BF; ++y ) {
      int offset_x_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_X_ODD + ( x * BATTLE_MAP_SPRITE_X_DELTA );
      int offset_y_temp = BATTLE_MAP_SPRITE_INITIAL_OFFSET_Y_ODD + ( ( 5 - ( y / 2 ) ) * BATTLE_MAP_SPRITE_Y_DELTA );

      // adjust if even
      if ( ( y % 2 == 0 ) ) {
        offset_x_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_X;
        offset_y_temp += BATTLE_MAP_SPRITE_ADJUST_EVEN_Y;
      }
      double hex_center_x = double( offset_x_temp ) + ( HEXAGON_SPRITE_WIDTH / 2.0 );
      double hex_center_y = double( offset_y_temp ) + ( HEXAGON_SPRITE_HEIGHT / 2.0 );

      if ( pointInHexagon( mx, my, hex_center_x, hex_center_y ) ) {
        return CoordPair( x, y );
      }
    }
  }
  return std::nullopt;
}

bool MouseHandler::pointInHexagon( int px, int py, double hex_x, double hex_y ) const noexcept {
  double dx = std::abs( px - hex_x );
  double dy = std::abs( py - hex_y );

  double dx_squared = dx * dx;
  double dy_squared = dy * dy;

  double distance_diagonal = std::sqrt( dx_squared + dy_squared );

  return distance_diagonal <= HEXAGON_SPRITE_MAX_RADIUS;
}

/* === @PUBLIC === */

void MouseHandler::updateMouseCoords( MouseCoords new_coords ) noexcept {
  mouse_coords_ = new_coords;
}

UserCommand MouseHandler::getCommand() noexcept {
  UserCommand moved_command = command_;
  command_ = None{};
  return moved_command;
}

void MouseHandler::visit( const GameStateOverworld& ) noexcept {
}

void MouseHandler::visit( const GameStateBattle& gbs ) noexcept {
  auto maybe_coords = getHexagonCoordsFromClick( mouse_coords_.x, mouse_coords_.y );
  if ( !maybe_coords.has_value() ) {
    return;
  }
  const auto possible_moves = gbs.viewBattle().getPossibleMoves();
  auto it = std::ranges::find_if(
      possible_moves, [&]( const std::shared_ptr<Move>& move ) { return move->destinationCoords() == *maybe_coords; } );
  if ( it == possible_moves.end() ) {
    return;
  }
  BattleCommand::Action action = [&]() -> BattleCommand::Action {  // TODO rewrite without dyn cas
    if ( dynamic_cast<MoveMove*>( ( *it ).get() ) != nullptr ) {
      return BattleCommand::Action::MOVE;
    }
    if ( dynamic_cast<AttackMove*>( ( *it ).get() ) != nullptr ) {
      return BattleCommand::Action::ATTACK;
    }
    if ( dynamic_cast<WaitMove*>( ( *it ).get() ) != nullptr ) {
      return BattleCommand::Action::WAIT;
    }
    err::abort( "unknown move type" );
  }();

  command_ = BattleCommand{ .action = action, .destination = *maybe_coords };
}