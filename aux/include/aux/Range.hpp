#pragma once

#include <type_traits>
template <typename RangeT, typename StepT>
requires( std::is_arithmetic<RangeT>() && std::is_arithmetic<StepT>()
          && ( std::is_same<RangeT, StepT>() || ( std::is_integral<RangeT>() && std::is_floating_point<StepT>() ) ) )
struct Range {
  RangeT min_val_;
  RangeT max_val_;
  RangeT step_;
};