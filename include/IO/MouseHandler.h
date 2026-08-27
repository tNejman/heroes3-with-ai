#pragma once

#include <optional>

#include "Game/UserCommand.h"
#include "Graphics/IRVisitor.h"
#include "Miscellaneous/Coords.h"

struct MouseCoords {
  int x;
  int y;
};

class MouseHandler : public IRVisitor {
 private:
  MouseCoords mouse_coords_;
  UserCommand command_ = None{};

  [[nodiscard]] std::optional<CoordPair> getHexagonCoordsFromClick( int mx, int my ) const noexcept;
  [[nodiscard]] bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const noexcept;

 public:
  void updateMouseCoords( MouseCoords ) noexcept;
  UserCommand getCommand() noexcept;

  void visit( const GameStateOverworld& ) noexcept override;
  void visit( const GameStateBattle& ) noexcept override;
};