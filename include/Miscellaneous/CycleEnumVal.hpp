#pragma once

#include <utility>

#include "Miscellaneous/EnumWithCount.hpp"

template <EnumWithCount T>
constexpr T next( T t ) {
  return static_cast<T>( ( std::to_underlying( t ) + 1 ) % std::to_underlying( T::COUNT ) );
}

template <EnumWithCount T>
constexpr T prev( T t ) {
  auto num_val = std::to_underlying( t );
  if ( num_val > 0 ) {
    return static_cast<T>( --num_val );
  }
  return static_cast<T>( std::to_underlying( T::COUNT ) - 1 );
}