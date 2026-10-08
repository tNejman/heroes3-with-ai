#pragma once

#include <cstdlib>
#include <meta>

[[noreturn]] inline void constexprCheckFailed( char const* condition_text ) {
  static_cast<void>( condition_text );
  std::abort();
}

#define CONSTEXPR_CHECK( condition )                          \
  do {                                                        \
    if ( !( condition ) ) constexprCheckFailed( #condition ); \
  } while ( false )
