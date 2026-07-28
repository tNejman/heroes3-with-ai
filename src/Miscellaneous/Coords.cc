#include "Miscellaneous/Coords.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <ostream>

/*
========== ShiftPair ==========
*/

ShiftPair ShiftPair::operator+( const ShiftPair& other ) const noexcept {
  return ShiftPair{ dx_ + other.dx_, dy_ + other.dy_ };
}

ShiftPair ShiftPair::operator-( const ShiftPair& other ) const noexcept {
  return ShiftPair{ dx_ - other.dx_, dy_ - other.dy_ };
}

/*
========== CoordPair ==========
*/

CoordPair CoordPair::operator+( const CoordPair& other ) const noexcept {
  return CoordPair{ x_ + other.x_, y_ + other.y_ };
}

CoordPair CoordPair::operator+( const ShiftPair& shift ) const noexcept {
  // assert( x_ + shift.dx_ >= 0 && NEGATIVE_X_ASSERT_MSG );
  // assert( y_ + shift.dy_ >= 0 && NEGATIVE_Y_ASSERT_MSG );
  return CoordPair{ x_ + shift.dx_, y_ + shift.dy_ };
}

CoordPair CoordPair::operator-( const CoordPair& other ) const noexcept {
  // assert( x_ - other.x_ >= 0 && NEGATIVE_X_ASSERT_MSG );
  // assert( y_ - other.y_ >= 0 && NEGATIVE_Y_ASSERT_MSG );
  return CoordPair{ x_ - other.x_, y_ - other.y_ };
}

CoordPair& CoordPair::operator+=( const CoordPair& other ) noexcept {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

CoordPair& CoordPair::operator+=( const ShiftPair& shift ) noexcept {
  // assert( x_ - shift.dx_ >= 0 && NEGATIVE_X_ASSERT_MSG );
  // assert( y_ - shift.dy_ >= 0 && NEGATIVE_Y_ASSERT_MSG );
  x_ += shift.dx_;
  y_ += shift.dy_;
  return *this;
}

std::ostream& operator<<( std::ostream& os, const CoordPair& coord ) noexcept {
  os << "(" << coord.x_ << ", " << coord.y_ << ")";
  return os;
}

double CoordPair::distanceFrom( const CoordPair& other ) const noexcept {
  return std::hypot( other.x_ - x_, other.y_ - y_ );
}

[[nodiscard]] size_t CoordPair::xAsId() const noexcept {
  return static_cast<size_t>( x_ );
}
[[nodiscard]] size_t CoordPair::yAsId() const noexcept {
  return static_cast<size_t>( y_ );
}