#pragma once
#include <exception>
#include <string>

class InvalidFactionTypeException : public std::exception {
 private:
  std::string message;

 public:
  InvalidFactionTypeException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};