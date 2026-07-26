#pragma once

#include <exception>
#include <string>

class InvalidSlotException : public std::exception {
 private:
  std::string message;

 public:
  InvalidSlotException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};