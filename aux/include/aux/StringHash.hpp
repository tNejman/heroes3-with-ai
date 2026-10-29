#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

struct StringHash {
  using is_transparent = void;

  std::size_t operator()( std::string_view text ) const noexcept {
    return std::hash<std::string_view>{}( text );
  }
};

template <typename T>
using StringMap = std::unordered_map<std::string, T, StringHash, std::equal_to<>>;