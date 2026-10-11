#pragma once

#include <optional>

#include "core/Game/UserCommand.hpp"
#include "engine/Graphics/IRVisitor.h"
#include "engine/IGame/Coords.h"

struct MouseCoords {
  int x;
  int y;
};

class MouseHandler : public IRVisitor {
 private:
  MouseCoords mouse_coords_;
  game::UserCommandcommand_ = None{};

  [[nodiscard]] std::optional<CoordPair> getHexagonCoordsFromClick( int mx, int my ) const noexcept;
  [[nodiscard]] bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const noexcept;

 public:
  void updateMouseCoords( MouseCoords ) noexcept;
  game::UserCommandgetCommand() noexcept;

  void visit( const game::StateOverworld& state ) noexcept override;
  void visit( const game::StateBattle& state ) noexcept override;
};