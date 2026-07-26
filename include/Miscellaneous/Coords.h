#pragma once

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <functional>
#include <cmath>

#include "Exceptions/CoordinateOutOfBoutdsException.hpp"

/**
 * @brief
 * ShiftPair represents a shift whether positive or negative
 * in cartesian coordinate system
 *
 * @param dx_
 * Shift either left or right
 * @param dy_
 * Shift either up or down
 */
class ShiftPair {
 public:
  int dx_;
  int dy_;

  ShiftPair( std::integral auto dx, std::integral auto dy )
      : dx_( dx ), dy_( dy ) {};
  ShiftPair( const ShiftPair& other ) noexcept;
  ShiftPair( const ShiftPair&& other ) noexcept;
  inline explicit constexpr ShiftPair(int dx, int dy) noexcept 
  :  dx_(dx), dy_(dy) {}
  ~ShiftPair() noexcept = default;

  ShiftPair& operator=( const ShiftPair& other ) noexcept;
  ShiftPair& operator+( const ShiftPair& other ) noexcept;
  ShiftPair& operator-( const ShiftPair& other ) noexcept;
  bool operator==( const ShiftPair& other ) const noexcept;
  bool operator!=( const ShiftPair& other ) const noexcept;
};

/**
 * @brief
 * CoordPair represents a pair of strictly positive
 * coordinates in cartesian coordinate system
 *
 * @param x_
 * x coordinate
 * @param y_
 * y coordinate
 */
class CoordPair {
 public:
  uint32_t x_;
  uint32_t y_;

  CoordPair( std::unsigned_integral auto x, std::unsigned_integral auto y )
      : x_( x ), y_( y ) {}
  CoordPair( const CoordPair& other ) noexcept;
  CoordPair( const CoordPair&& other ) noexcept;
  inline explicit constexpr CoordPair(uint32_t x, uint32_t y) noexcept 
  : x_(x), y_(y) {}
  ~CoordPair() noexcept = default;

  CoordPair& operator=( const CoordPair& other ) noexcept;
  CoordPair& operator+( const CoordPair& other ) noexcept;
  CoordPair& operator+( const ShiftPair& shift );
  CoordPair& operator-( const CoordPair& other );
  CoordPair& operator+=( const ShiftPair& shift );
  friend std::ostream& operator<<(std::ostream& os, const CoordPair& coord);
  bool operator==( const CoordPair& other ) const noexcept;
  bool operator!=( const CoordPair& other ) const noexcept;

  // @Warning lexicographical order, please do not use without a thought
  bool operator<( const CoordPair& other ) const noexcept;
  bool operator<=( const CoordPair& other ) const noexcept;
  bool operator>( const CoordPair& other ) const noexcept;
  bool operator>=( const CoordPair& other ) const noexcept;

  double distance( const CoordPair& other) const;
};