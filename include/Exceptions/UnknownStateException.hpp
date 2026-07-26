#pragma once

#include <exception>
#include <string>

class UnknownStateException : public std::exception {
 private:
  std::string message;

 public:
  UnknownStateException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};