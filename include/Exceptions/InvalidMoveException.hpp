#pragma once

#include <exception>
#include <string>
#include <utility>

class InvalidMoveException : public std::exception {
 private:
  std::string message_;

 public:
  InvalidMoveException( std::string msg ) : message_( std::move( msg ) ) {
  }

  [[nodiscard]] const char* what() const noexcept override {
    return message_.c_str();
  }
};