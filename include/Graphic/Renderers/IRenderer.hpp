#pragma once

#include "Graphic/SpriteVisitor.h"

template <class T>
class IRenderer {
 protected:
  std::shared_ptr<SpriteVisitor> sprite_visitor_;
  std::shared_ptr<T> object_;

 public:
  IRenderer( std::shared_ptr<SpriteVisitor> sprite_visitor, std::shared_ptr<T> object ) : sprite_visitor_( sprite_visitor ), object_( object ) {};
  virtual ~IRenderer() = default;
  virtual void render( sf::RenderWindow& window, const CoordPair center_coords ) = 0;
};