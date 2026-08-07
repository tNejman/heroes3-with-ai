#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>
#include <memory>
#include <utility>

#include "Graphics/SpriteVisitor.h"
#include "Miscellaneous/Coords.h"

template <class T>
class IRenderer {
 protected:
  std::shared_ptr<SpriteVisitor> sprite_visitor_;
  std::reference_wrapper<T> object_;

 public:
  IRenderer( std::shared_ptr<SpriteVisitor> sprite_visitor, T& object )
      : sprite_visitor_( std::move( sprite_visitor ) ), object_( object ) {};
  virtual ~IRenderer() = default;
  virtual void render( sf::RenderWindow& window, CoordPair center_coords ) = 0;
};