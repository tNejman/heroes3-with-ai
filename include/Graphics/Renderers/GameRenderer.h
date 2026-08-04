#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <optional>

#include "Game/KeyboardHandler.h"
#include "Graphics/Renderers/MapRenderer.h"
#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"

class GameGraphicIntegrator {
 private:
  std::shared_ptr<sf::RenderWindow> render_window_;
  SpriteVisitor sprite_visitor_;
  MapRenderer map_renderer_;
  KeyHandler key_handler_;

  int mouse_x_ = 0;
  int mouse_y_ = 0;
  bool waiting_for_print_ = true;
  int frames_since_start_ = 0;

  [[nodiscard]] bool pointInHexagon( int px, int py, double hex_x, double hex_y ) const;
  std::optional<CoordPair> getCoordsFromClick();

 public:
  void setMouseCoords( int x, int y );
  [[nodiscard]] std::shared_ptr<sf::RenderWindow> getRenderWindow();
  [[nodiscard]] int getFrameCountSinceStart() const noexcept;
};