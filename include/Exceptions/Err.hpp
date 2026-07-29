#pragma once
#include <source_location>
#include <string>
#include <string_view>

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
  throw E{ std::string{ scope( loc.function_name() ) } + " -> " + std::string{ text } };
}

}  // namespace err