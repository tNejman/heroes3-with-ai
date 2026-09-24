#pragma once

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <optional>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T, typename... Ts>
constexpr std::size_t COUNT_OF{ ( std::size_t{ std::is_same_v<T, Ts> } + ... + 0 ) };

template <typename T, typename... Ts>
constexpr std::size_t INDEX_OF{ [] {
  constexpr bool MATCH[]{ std::is_same_v<T, Ts>... };
  std::size_t i{ 0 };
  while ( !MATCH[i] ) {
    ++i;
  }
  return i;
}() };

template <typename Product, typename... Fields>
class Builder {
  static_assert( ( ( COUNT_OF<Fields, Fields...> == 1 ) && ... ), "duplicate field tag" );

 public:
  template <typename F>
  [[nodiscard]] Builder&& set( typename F::type value ) && noexcept(
      std::is_nothrow_move_constructible_v<typename F::type> && std::is_nothrow_move_assignable_v<typename F::type> ) {
    static_assert( COUNT_OF<F, Fields...> == 1, "field not part of this builder" );
    std::get<INDEX_OF<F, Fields...>>( values_ ) = std::move( value );
    return std::move( *this );
  }

  void reset() noexcept {
    std::apply( []( auto&... opt ) { ( opt.reset(), ... ); }, values_ );
  }

  [[nodiscard]] Product build() && {
    return buildImpl( std::index_sequence_for<Fields...>{} );
  }

 private:
  template <std::size_t... I>
  Product buildImpl( [[maybe_unused]] std::index_sequence<I...> index_sec ) {
    return Product{ take<Fields, I>()... };
  }

  template <typename F, std::size_t I>
  typename F::type take() {
    auto& opt{ std::get<I>( values_ ) };
    if ( !opt ) {
      return F::preset();
    }
    return std::move( *opt );
  }

  std::tuple<std::optional<typename Fields::type>...> values_;
};

/* =========================== */

template <typename Inside, auto Default>
requires( std::constructible_from<Inside, decltype( Default )> )
struct BMember {
  static Inside preset() {
    return Inside{ Default };
  }
};

template <size_t N>
struct FixedString {
  char data[N]{};

  constexpr FixedString( const char ( &str )[N] ) {
    std::copy_n( str, N, data );
  }

  constexpr operator std::string_view() const {
    return std::string_view{ data, N - 1 };
  }
};