#pragma once

#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>

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
struct ShiftPair {
 public:
  int dx_{ 0 };  // NOLINT(misc-non-private-member-variables-in-classes)
  int dy_{ 0 };  // NOLINT(misc-non-private-member-variables-in-classes)

  // explicit constexpr ShiftPair( int dx, int dy ) noexcept;
  // constexpr ShiftPair( const ShiftPair& other ) noexcept = default;
  // constexpr ShiftPair( ShiftPair&& other ) noexcept = default;
  // constexpr ShiftPair& operator=( const ShiftPair& other ) noexcept = default;
  // constexpr ShiftPair& operator=( ShiftPair&& other ) noexcept = default;
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
  uint32_t x_{ 0 };
  uint32_t y_{ 0 };

  // explicit constexpr CoordPair( uint32_t x, uint32_t y ) noexcept;

  CoordPair& operator+( const CoordPair& other ) noexcept;
  CoordPair& operator+( const ShiftPair& shift );
  CoordPair& operator-( const CoordPair& other );
  CoordPair& operator+=( const ShiftPair& shift );
  friend std::ostream& operator<<( std::ostream& os, const CoordPair& coord );  // TODO make run only in debug
  bool operator==( const CoordPair& other ) const noexcept;
  bool operator!=( const CoordPair& other ) const noexcept;

  // @Warning lexicographical order, please do not use without a thought
  bool operator<( const CoordPair& other ) const noexcept;
  bool operator<=( const CoordPair& other ) const noexcept;
  bool operator>( const CoordPair& other ) const noexcept;
  bool operator>=( const CoordPair& other ) const noexcept;

  double distance( const CoordPair& other ) const;
};