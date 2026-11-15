#pragma once

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>

inline std::string& toLower( std::string& str ) noexcept {
  std::ranges::transform( str, str.begin(), []( unsigned char c ) { return std::tolower( c ); } );
  return str;
}

[[nodiscard]] inline std::string&& toLower( std::string&& str ) noexcept {
  std::ranges::transform( str, str.begin(), []( unsigned char c ) { return std::tolower( c ); } );
  return std::move( str );
}

[[nodiscard]] inline std::string toLower( std::string_view str ) noexcept {
  std::string out;
  out.reserve( str.size() );
  std::ranges::transform( str, std::back_inserter( out ), []( unsigned char c ) { return std::tolower( c ); } );
  return out;
}