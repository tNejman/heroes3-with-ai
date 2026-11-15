#pragma once

#include <algorithm>
#include <cstddef>
#include <string_view>

template <std::size_t N>
struct FixedString {
  char data[N]{};

  [[nodiscard]] constexpr FixedString( const char ( &str )[N] ) noexcept {
    std::copy_n( str, N, data );
  }

  [[nodiscard]] constexpr std::string_view view() const noexcept {
    return std::string_view{ data, N - 1 };
  }
};