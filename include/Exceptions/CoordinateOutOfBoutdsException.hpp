#pragma once

#include <exception>
#include <string>

class CoordinateOutOfBoundsException : public std::exception {
 private:
  std::string message;

 public:
  CoordinateOutOfBoundsException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};