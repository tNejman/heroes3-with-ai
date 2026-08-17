#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <functional>
#include <memory>
#include <utility>

#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"

template <class T>
class IRenderer {
 protected:
  std::reference_wrapper<sf::RenderWindow> window_;
  static inline std::shared_ptr<SpriteVisitor> sprite_visitor = std::make_shared<SpriteVisitor>();
  std::reference_wrapper<const T> object_;

 public:
  IRenderer( sf::RenderWindow& window, const T& object ) : window_( window ), object_( object ) {};
  virtual ~IRenderer() = default;
  virtual void render() = 0;
};