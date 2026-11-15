#pragma once

#include <exception>
#include <format>
#include <string>
#include <utility>

#include "engine/model/IGame/Coords.h"

#include "core/Misc/Formatter.hpp"  // IWYU pragma: keep

class InvalidMapMoveException : public std::exception {
 private:
  std::string message_;

 public:
  [[nodiscard]] constexpr InvalidMapMoveException( std::string msg ) noexcept : message_( std::move( msg ) ) {
  }
  [[nodiscard]] InvalidMapMoveException( std::string msg, CoordPair coords ) noexcept
      : message_( std::format( "{}, {}", msg, coords ) ) {
  }

  [[nodiscard]] constexpr const char* what() const noexcept override {
    return message_.c_str();
  }
};