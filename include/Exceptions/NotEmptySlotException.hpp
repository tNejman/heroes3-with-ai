#pragma once

#include <exception>
#include <string>

class NotEmptySlotException : public std::exception {
 private:
  std::string message;

 public:
  NotEmptySlotException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};