#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <functional>
#include <memory>

#include "engine/Graphics/SpriteVisitor.h"

template <class T>
class IRenderer {
 protected:
  std::reference_wrapper<sf::RenderTexture> target_render_texture_;
  static inline std::shared_ptr<SpriteVisitor> sprite_visitor = std::make_shared<SpriteVisitor>();
  std::reference_wrapper<const T> object_;

 public:
  IRenderer() = delete;
  IRenderer( const IRenderer& ) = delete;
  IRenderer( IRenderer&& ) = delete;
  IRenderer& operator=( const IRenderer& ) = delete;
  IRenderer& operator=( IRenderer&& ) = delete;
  IRenderer( sf::RenderTexture& target_render_texture, const T& object )
      : target_render_texture_( target_render_texture ), object_( object ) {};
  virtual ~IRenderer() = default;
  virtual void render() = 0;
};