#pragma once

#include <algorithm>
#include <cstddef>
#include <string_view>

template <std::size_t N>
struct FixedString {
  char data[N]{};

  constexpr FixedString( const char ( &str )[N] ) {
    std::copy_n( str, N, data );
  }

  [[nodiscard]] constexpr std::string_view view() const noexcept {
    return std::string_view{ data, N - 1 };
  }
};