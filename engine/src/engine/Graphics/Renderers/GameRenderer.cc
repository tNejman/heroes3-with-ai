#include "engine/Graphics/Renderers/GameRenderer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>

#include "core/Game/Game.h"
#include "engine/Graphics/RVisitor.h"
#include "engine/Graphics/Renderers/IRenderer.hpp"

GameRenderer::GameRenderer( sf::RenderWindow& window, sf::RenderTexture& target_render_texture,
                            const Game& game ) noexcept
    : IRenderer<Game>( target_render_texture, game ), window_( window ) {
}

void GameRenderer::render() {
  window_.get().clear( sf::Color::Black );
  target_render_texture_.get().clear( sf::Color::Black );

  RVisitor state_visitor{ target_render_texture_, object_.get().getContext() };
  object_.get().getState().accept( state_visitor );

  target_render_texture_.get().display();

  sf::Sprite screen{ target_render_texture_.get().getTexture() };
  const sf::Vector2u win_size = window_.get().getSize();
  const sf::Vector2u tex_size = target_render_texture_.get().getSize();
  screen.setScale( { static_cast<float>( win_size.x ) / static_cast<float>( tex_size.x ),
                     static_cast<float>( win_size.y ) / static_cast<float>( tex_size.y ) } );
  window_.get().draw( screen );

  window_.get().display();
}