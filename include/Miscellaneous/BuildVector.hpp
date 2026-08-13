#pragma once

#include <type_traits>
#include <vector>

template <class T, class... Ts>
std::vector<T> buildVector( Ts&&... xs ) {
  std::vector<T> v;
  v.reserve( sizeof...( xs ) );
  ( v.emplace_back( std::forward<Ts>( xs ) ), ... );
  return v;
}

template <class... Ts>
auto buildVector( Ts&&... xs ) {
  using T = std::common_type_t<std::decay_t<Ts>...>;
  std::vector<T> v;
  v.reserve( sizeof...( xs ) );
  ( v.emplace_back( std::forward<Ts>( xs ) ), ... );
  return v;
}