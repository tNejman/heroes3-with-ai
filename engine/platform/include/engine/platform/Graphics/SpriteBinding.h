#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <concepts>
#include <functional>
#include <optional>
#include <string_view>
#include <type_traits>

#include "aux/Enum.hpp"

using TextureCleanupFun = std::function<void( sf::Texture )>;

struct TextureSource {
  std::string_view path_;
  std::optional<sf::IntRect> crop_;
  TextureCleanupFun tex_cleanup_fun_ = nullptr;
};

struct DefaultGlobalState {};

template <typename Object, typename GlobalState = DefaultGlobalState>
struct SpriteBinding {
  static constexpr bool IS_UNBOUND = true;
};

namespace sprite_binding_detail {

template <typename Object, typename GlobalState>
concept Specialized = !requires { SpriteBinding<Object, GlobalState>::IS_UNBOUND; };

}  // namespace sprite_binding_detail

template <typename Object, typename GlobalState>
using ResolvedSpriteBinding =
    std::conditional_t<sprite_binding_detail::Specialized<Object, GlobalState>, SpriteBinding<Object, GlobalState>,
                       SpriteBinding<Object, DefaultGlobalState>>;

template <typename Object, typename GlobalState, typename... Params>
concept SpriteBound = ( Enum<Params> && ... ) && requires( Params... params ) {
  { ResolvedSpriteBinding<Object, GlobalState>::source( params... ) } -> std::same_as<TextureSource>;
};