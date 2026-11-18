#pragma once

#include <cassert>
#include <cmath>
#include <concepts>
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
  [[nodiscard]] constexpr ShiftPair( int dx, int dy ) noexcept;

  [[nodiscard]] constexpr ShiftPair operator+( const ShiftPair& other ) const noexcept;
  [[nodiscard]] constexpr ShiftPair operator-( const ShiftPair& other ) const noexcept;
  auto operator<=>( const ShiftPair& other ) const noexcept = default;
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
struct CoordPair {
  int x_;  // NOLINT(misc-non-private-member-variables-in-classes)
  int y_;  // NOLINT(misc-non-private-member-variables-in-classes)

  CoordPair() = delete;

  [[nodiscard]] constexpr CoordPair( std::integral auto x, std::integral auto y ) noexcept;

  [[nodiscard]] constexpr CoordPair operator+( const CoordPair& other ) const noexcept;
  [[nodiscard]] constexpr CoordPair operator+( const ShiftPair& shift ) const noexcept;
  [[nodiscard]] constexpr CoordPair operator-( const CoordPair& other ) const noexcept;
  constexpr CoordPair& operator+=( const CoordPair& other ) noexcept;
  constexpr CoordPair& operator+=( const ShiftPair& shift ) noexcept;
  constexpr friend std::ostream& operator<<( std::ostream& os,
                                             const CoordPair& coord ) noexcept;  // TODO make run only in debug
  [[nodiscard]] constexpr auto operator<=>( const CoordPair& other ) const noexcept = default;

  [[nodiscard]] constexpr double distanceFrom( const CoordPair& other ) const noexcept;
  [[nodiscard]] constexpr size_t xAsId() const noexcept;
  [[nodiscard]] constexpr size_t yAsId() const noexcept;
};

/* ==== CONSTEXPR DEFINITIONS ==== */

/*
========== ShiftPair ==========
*/

[[nodiscard]] constexpr ShiftPair::ShiftPair( int dx, int dy ) noexcept : dx_( dx ), dy_( dy ) {
}

[[nodiscard]] constexpr ShiftPair ShiftPair::operator+( const ShiftPair& other ) const noexcept {
  return ShiftPair{ dx_ + other.dx_, dy_ + other.dy_ };
}

[[nodiscard]] constexpr ShiftPair ShiftPair::operator-( const ShiftPair& other ) const noexcept {
  return ShiftPair{ dx_ - other.dx_, dy_ - other.dy_ };
}

/*
========== CoordPair ==========
*/

[[nodiscard]] constexpr CoordPair::CoordPair( std::integral auto x, std::integral auto y ) noexcept
    : x_( static_cast<int>( x ) ), y_( static_cast<int>( y ) ) {
}

[[nodiscard]] constexpr CoordPair CoordPair::operator+( const CoordPair& other ) const noexcept {
  return CoordPair{ x_ + other.x_, y_ + other.y_ };
}

[[nodiscard]] constexpr CoordPair CoordPair::operator+( const ShiftPair& shift ) const noexcept {
  return CoordPair{ x_ + shift.dx_, y_ + shift.dy_ };
}

[[nodiscard]] constexpr CoordPair CoordPair::operator-( const CoordPair& other ) const noexcept {
  return CoordPair{ x_ - other.x_, y_ - other.y_ };
}

constexpr CoordPair& CoordPair::operator+=( const CoordPair& other ) noexcept {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

constexpr CoordPair& CoordPair::operator+=( const ShiftPair& shift ) noexcept {
  x_ += shift.dx_;
  y_ += shift.dy_;
  return *this;
}

[[nodiscard]] constexpr std::ostream& operator<<( std::ostream& os, const CoordPair& coord ) noexcept {
  os << "(" << coord.x_ << ", " << coord.y_ << ")";
  return os;
}

[[nodiscard]] constexpr double CoordPair::distanceFrom( const CoordPair& other ) const noexcept {
  return std::hypot( other.x_ - x_, other.y_ - y_ );
}

[[nodiscard]] constexpr size_t CoordPair::xAsId() const noexcept {
  return static_cast<size_t>( x_ );
}

[[nodiscard]] constexpr size_t CoordPair::yAsId() const noexcept {
  return static_cast<size_t>( y_ );
}