#pragma once

#include <algorithm>
#include <meta>
#include <string_view>

#include "aux/FixedString.hpp"

consteval bool hasMethod( std::meta::info type, std::string_view name, std::meta::info signature ) {
  return std::ranges::any_of(
      std::meta::members_of( type, std::meta::access_context::current() ), [&]( std::meta::info member ) {
        return ( std::meta::is_function( member ) || std::meta::is_function_template( member ) )
               && std::meta::has_identifier( member ) && std::meta::identifier_of( member ) == name
               && std::meta::is_same_type( std::meta::type_of( member ), signature );
      } );
}

template <typename ClassCheckedForFunctionPresence, FixedString FunctionName, typename FunctionSignature>
concept hasMethod_c = ( hasMethod( ^^ClassCheckedForFunctionPresence, FunctionName, ^^FunctionSignature ) );