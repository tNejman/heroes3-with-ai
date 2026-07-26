#pragma once

#include <exception>
#include <string>

class EmptySlotException : public std::exception {
 private:
  std::string message;

 public:
  EmptySlotException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};