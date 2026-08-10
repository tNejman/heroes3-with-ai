#pragma once

#include <cassert>
#include <cstddef>
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
  int dx_;  // NOLINT(misc-non-private-member-variables-in-classes)
  int dy_;  // NOLINT(misc-non-private-member-variables-in-classes)

  ShiftPair() = delete;
  constexpr ShiftPair( int dx, int dy ) : dx_( dx ), dy_( dy ) {
  }

  ShiftPair operator+( const ShiftPair& other ) const noexcept;
  ShiftPair operator-( const ShiftPair& other ) const noexcept;
  auto operator<=>( const ShiftPair& other ) const noexcept = default;
};

namespace {
// these two need to be macros; assert must take in literal
#define NEGATIVE_X_ASSERT_MSG "x_ in CoordPair must be non-negative"  // NOLINT(cppcoreguidelines-macro-usage)
#define NEGATIVE_Y_ASSERT_MSG "y_ in CoordPair must be non-negative"  // NOLINT(cppcoreguidelines-macro-usage)
}  // namespace

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
struct CoordPair {
  int x_;  // NOLINT(misc-non-private-member-variables-in-classes)
  int y_;  // NOLINT(misc-non-private-member-variables-in-classes)

  CoordPair() = delete;
  constexpr CoordPair( int x, int y ) noexcept  // NOLINT(bugprone-easily-swappable-parameters)
      : x_( x ), y_( y ) {
    // assert( x >= 0 && NEGATIVE_X_ASSERT_MSG );
    // assert( y >= 0 && NEGATIVE_Y_ASSERT_MSG );
  }

  CoordPair operator+( const CoordPair& other ) const noexcept;
  CoordPair operator+( const ShiftPair& shift ) const noexcept;
  CoordPair operator-( const CoordPair& other ) const noexcept;
  CoordPair& operator+=( const CoordPair& other ) noexcept;
  CoordPair& operator+=( const ShiftPair& shift ) noexcept;
  friend std::ostream& operator<<( std::ostream& os, const CoordPair& coord ) noexcept;  // TODO make run only in debug
  auto operator<=>( const CoordPair& other ) const noexcept = default;

  [[nodiscard]] double distanceFrom( const CoordPair& other ) const noexcept;
  [[nodiscard]] size_t xAsId() const noexcept;
  [[nodiscard]] size_t yAsId() const noexcept;
};