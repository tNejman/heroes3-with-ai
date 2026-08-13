#pragma once
#include <concepts>
#include <cstdlib>
#include <format>
#include <iostream>
#include <source_location>
#include <string_view>
#include <typeinfo>

namespace err {

constexpr std::string_view scope( std::string_view fn ) noexcept {
  if ( auto p = fn.find( '(' ); p != std::string_view::npos ) {
    fn.remove_suffix( fn.size() - p );  // drop "(...)" and trailing qualifiers
  }
  if ( auto s = fn.rfind( ' ' ); s != std::string_view::npos ) {
    fn.remove_prefix( s + 1 );  // drop return type -> "Foo::bar"
  }
  return fn;
}

constexpr std::string_view scopeFunName( std::source_location src = std::source_location::current() ) noexcept {
  return scope( src.function_name() );
}

template <class E>
[[noreturn]] void raise( std::string_view text, std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {} -> {}", typeid( E ).name(), scopeFunName( loc ), text ) };
}

template <class E>
[[noreturn]] void raise( std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {}", typeid( E ).name(), scopeFunName( loc ) ) };
}

template <class E, class Forward>
requires( !std::convertible_to<Forward, std::string_view> )
[[noreturn]] void raise( Forward arg, std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {}", typeid( E ).name(), scopeFunName( loc ) ), arg };
}

template <class E, class Forward>
requires( !std::convertible_to<Forward, std::string_view> )
[[noreturn]] void raise( std::string_view text, Forward arg,
                         std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {} -> {}", typeid( E ).name(), scopeFunName( loc ), text ), arg };
}

template <typename... Args>
inline void passCondOrAbort( bool condition, Args&&... msgs ) {
  if ( !condition ) {
    ( std::cout << ... << std::forward<Args>( msgs ) ) << '\n';
    std::abort();
  }
}

template <typename E, typename... Args>
inline void passCondOrThrow( bool condition, Args&&... args ) {
  if ( !condition ) {
    raise<E>( std::forward<Args>( args )... );
  }
}

#define SINGLE_CALL_GUARD( ... )                                                         \
  static bool is_first_call = true;                                                      \
  err::passCondOrAbort( is_first_call, err::scopeFunName() __VA_OPT__(, ) __VA_ARGS__ ); \
  is_first_call = false;

}  // namespace err