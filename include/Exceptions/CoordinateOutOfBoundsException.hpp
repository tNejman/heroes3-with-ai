#pragma once

#include <exception>
#include <format>
#include <string>
#include <utility>

#include "Miscellaneous/Coords.h"

class CoordinateOutOfBoundsException : public std::exception {
 private:
  std::string message_;

 public:
  CoordinateOutOfBoundsException( std::string msg ) : message_( std::move( msg ) ) {
  }
  CoordinateOutOfBoundsException( CoordPair coords ) : message_( std::format( "x={}, y={}", coords.x_, coords.y_ ) ) {
  }
  CoordinateOutOfBoundsException( CoordPair coords, std::string msg )
      : message_( std::format( "{}, x={}, y={}", msg, coords.x_, coords.y_ ) ) {
  }

  [[nodiscard]] const char* what() const noexcept override {
    return message_.c_str();
  }
};