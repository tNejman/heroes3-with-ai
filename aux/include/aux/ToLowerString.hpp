#pragma once

#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>
#include <string_view>
#include <utility>

inline std::string& toLower( std::string& str ) {
  std::ranges::transform( str, str.begin(), []( unsigned char c ) { return std::tolower( c ); } );
  return str;
}

inline std::string&& toLower( std::string&& str ) {
  std::ranges::transform( str, str.begin(), []( unsigned char c ) { return std::tolower( c ); } );
  return std::move( str );
}

inline std::string toLower( std::string_view str ) {
  std::string out;
  out.reserve( str.size() );
  std::ranges::transform( str, std::back_inserter( out ), []( unsigned char c ) { return std::tolower( c ); } );
  return out;
}