#pragma once

#include <exception>
#include <format>
#include <string>
#include <utility>

#include "core/Misc/Formatter.hpp"  // IWYU pragma: keep
#include "engine/IGame/Coords.h"


class CoordinateOutOfBoundsException : public std::exception {
 private:
  std::string message_;

 public:
  CoordinateOutOfBoundsException( std::string msg ) : message_( std::move( msg ) ) {
  }
  CoordinateOutOfBoundsException( std::string msg, CoordPair coords )
      : message_( std::format( "{}, {}", msg, coords ) ) {
  }

  [[nodiscard]] const char* what() const noexcept override {
    return message_.c_str();
  }
};