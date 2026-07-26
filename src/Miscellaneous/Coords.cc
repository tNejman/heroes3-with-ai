#include "Miscellaneous/Coords.h"

#include <cmath>
#include <cstdint>
#include <ostream>

#include "Exceptions/CoordinateOutOfBoundsException.hpp"

/*
========== ShiftPair ==========
*/

// constexpr ShiftPair::ShiftPair( int dx, int dy ) noexcept : dx_( dx ), dy_( dy ) {
// }

ShiftPair& ShiftPair::operator+( const ShiftPair& other ) noexcept {
  dx_ += other.dx_;
  dy_ += other.dy_;
  return *this;
}

ShiftPair& ShiftPair::operator-( const ShiftPair& other ) noexcept {
  dx_ -= other.dx_;
  dy_ -= other.dy_;
  return *this;
}

bool ShiftPair::operator==( const ShiftPair& other ) const noexcept {
  return ( dx_ == other.dx_ && dy_ == other.dy_ );
}

bool ShiftPair::operator!=( const ShiftPair& other ) const noexcept {
  return ( dx_ != other.dx_ || dy_ != other.dy_ );
}

/*
========== CoordPair ==========
*/

// constexpr CoordPair::CoordPair( uint32_t x, uint32_t y ) noexcept : x_( x ), y_( y ) {
// }

CoordPair& CoordPair::operator+( const CoordPair& other ) noexcept {
  x_ += other.x_;
  y_ += other.y_;
  return *this;
}

CoordPair& CoordPair::operator+( const ShiftPair& shift ) {
  int x_tmp = short( x_ ) + shift.dx_;
  int y_tmp = short( y_ ) + shift.dy_;
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "Reached negative coordinates" );
  } else {
    x_ = uint32_t( x_tmp );
    y_ = uint32_t( y_tmp );
    return *this;
  }
}

CoordPair& CoordPair::operator-( const CoordPair& other ) {
  int x_tmp = int( x_ ) - int( other.x_ );
  int y_tmp = int( y_ ) - int( other.y_ );
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "Reached negative coordinates" );
  } else {
    x_ = uint32_t( x_tmp );
    y_ = uint32_t( y_tmp );
    return *this;
  }
}

CoordPair& CoordPair::operator+=( const ShiftPair& shift ) {
  int x_tmp = int( x_ ) + shift.dx_;
  int y_tmp = int( y_ ) + shift.dy_;
  if ( x_tmp < 0 || y_tmp < 0 ) {
    throw CoordinateOutOfBoundsException( "Reached negative coordinates" );
  } else {
    x_ = uint32_t( x_tmp );
    y_ = uint32_t( y_tmp );
    return *this;
  }
}

std::ostream& operator<<( std::ostream& os, const CoordPair& coord ) {
  os << "(" << coord.x_ << ", " << coord.y_ << ")";
  return os;
}

bool CoordPair::operator==( const CoordPair& other ) const noexcept {
  return ( x_ == other.x_ && y_ == other.y_ );
}

bool CoordPair::operator!=( const CoordPair& other ) const noexcept {
  return ( x_ != other.x_ || y_ != other.y_ );
}

bool CoordPair::operator<( const CoordPair& other ) const noexcept {
  return ( x_ < other.x_ ) || ( x_ == other.x_ && y_ < other.y_ );
}

bool CoordPair::operator<=( const CoordPair& other ) const noexcept {
  return ( *this == other ) || ( x_ < other.x_ ) || ( x_ == other.x_ && y_ < other.y_ );
}

bool CoordPair::operator>( const CoordPair& other ) const noexcept {
  return ( x_ > other.x_ ) || ( x_ == other.x_ && y_ > other.y_ );
}

bool CoordPair::operator>=( const CoordPair& other ) const noexcept {
  return ( *this == other ) || ( x_ > other.x_ ) || ( x_ == other.x_ && y_ > other.y_ );
}

double CoordPair::distance( const CoordPair& other ) const {
  // if this = 0,0 and other = 4,3 the result will be 5

  return sqrt( std::pow( (double)( (int)other.x_ - (int)this->x_ ), 2 )
               + std::pow( (double)( (int)other.y_ - (int)this->y_ ), 2 ) );
}