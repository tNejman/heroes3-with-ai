#pragma once
#include <concepts>
#include <format>
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

template <class E>
[[noreturn]] void raise( std::string_view text, std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {} -> {}", typeid( E ).name(), scope( loc.function_name() ), text ) };
}

template <class E>
[[noreturn]] void raise( std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {}", typeid( E ).name(), scope( loc.function_name() ) ) };
}

template <class E, class Forward>
requires( !std::convertible_to<Forward, std::string_view> )
[[noreturn]] void raise( Forward arg, std::source_location loc = std::source_location::current() ) {
  throw E{ std::format( "{} -> {}", typeid( E ).name(), scope( loc.function_name() ) ), arg };
}

}  // namespace err