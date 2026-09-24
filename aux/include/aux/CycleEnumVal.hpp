#pragma once

#include <magic_enum/magic_enum.hpp>
#include <utility>

#include "aux/Enum.hpp"

template <Enum E>
constexpr E next( E e ) {
  return static_cast<E>( ( std::to_underlying( e ) + 1 ) % magic_enum::enum_count<E>() );
}

template <Enum E>
constexpr E prev( E e ) {
  auto num_val = std::to_underlying( e );
  if ( num_val > 0 ) {
    return static_cast<E>( --num_val );
  }
  return static_cast<E>( magic_enum::enum_count<E>() - 1 );
}