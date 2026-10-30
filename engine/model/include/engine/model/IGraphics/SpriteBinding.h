#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <concepts>
#include <functional>
#include <optional>
#include <string>
#include <type_traits>

#include "aux/Enum.hpp"

static const inline std::string DEFAULT_TEX_FILE_FORMAT = ".png";

struct TextureSource {
  std::string path_prefix_;
  std::string path_;
  std::string path_suffix_ = DEFAULT_TEX_FILE_FORMAT;
  std::optional<sf::IntRect> crop_ = std::nullopt;
  std::function<void( sf::Texture& )> tex_cleanup_fun_ = nullptr;
  std::function<void( sf::Sprite& )> sprite_cleanup_fun_ = nullptr;

  [[nodiscard]] std::string getFullPath() const noexcept {
    return path_prefix_ + path_ + path_suffix_;
  }
};

namespace game {

class IState;

}  // namespace game

/**
 * @brief Specialize per rendered object type, optionally per global state type:
 *
 *   static constexpr TextureSource source( Params... ) noexcept;
 *
 * Every Param satisfies Enum. Params cover both object parameters and local state.
 * Zero params: one file per object, regardless of its parameters.
 * source() may be overloaded to accept several parameter sets.
 *
 * Lookup for ( Object, GlobalState ) falls back to ( Object, IState ) when not specialized.
 */
template <typename Object, std::derived_from<game::IState> GlobalState = game::IState>
struct SpriteBinding {
  static constexpr bool IS_UNBOUND = true;
};

namespace sprite_binding_detail {

template <typename Object, typename GlobalState>
concept Specialized = !requires { SpriteBinding<Object, GlobalState>::IS_UNBOUND; };

}  // namespace sprite_binding_detail

template <typename Object, std::derived_from<game::IState> GlobalState = game::IState>
using ResolvedSpriteBinding =
    std::conditional_t<sprite_binding_detail::Specialized<Object, GlobalState>, SpriteBinding<Object, GlobalState>,
                       SpriteBinding<Object, game::IState>>;

template <typename Object, typename GlobalState, typename... Params>
concept SpriteBound = std::derived_from<GlobalState, game::IState> && ( Enum<Params> && ... )
                      && requires( const Object& object, Params... params ) {
                           {
                             ResolvedSpriteBinding<Object, GlobalState>::source( object, params... )
                           } -> std::same_as<TextureSource>;
                         };