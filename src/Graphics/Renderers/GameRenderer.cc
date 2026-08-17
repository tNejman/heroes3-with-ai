#include "Graphics/Renderers/GameRenderer.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window/Window.hpp>

#include "Game/Game.h"
#include "Graphics/RVisitor.h"
#include "Graphics/Renderers/IRenderer.hpp"

GameRenderer::GameRenderer( sf::RenderWindow& window, const Game& game ) : IRenderer<Game>( window, game ) {
}

void GameRenderer::render() {
  window_.get().clear( sf::Color::Black );

  RVisitor state_visitor{ window_, object_.get().getContext() };
  object_.get().getState().accept( state_visitor );

  window_.get().display();
}