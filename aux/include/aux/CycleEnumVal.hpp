#pragma once

#include <utility>

#include <magic_enum/magic_enum.hpp>

#include "aux/Enum.hpp"

template <Enum E>
[[nodiscard]] constexpr E next( E e ) noexcept {
  return static_cast<E>( ( std::to_underlying( e ) + 1 ) % magic_enum::enum_count<E>() );
}

template <Enum E>
[[nodiscard]] constexpr E prev( E e ) noexcept {
  auto num_val = std::to_underlying( e );
  if ( num_val > 0 ) {
    return static_cast<E>( --num_val );
  }
  return static_cast<E>( magic_enum::enum_count<E>() - 1 );
}