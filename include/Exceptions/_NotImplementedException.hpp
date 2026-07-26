#pragma once

#include <exception>
#include <string>

class NotImplementedException : public std::exception {
 private:
  std::string message;

 public:
  NotImplementedException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};