#pragma once

#include <exception>
#include <string>

class InvalidMoveException : public std::exception {
 private:
  std::string message;

 public:
  InvalidMoveException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};