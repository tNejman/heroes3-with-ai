#pragma once

#include <exception>
#include <string>

class InvalidInputFileException : public std::exception {
 private:
  std::string message;

 public:
  InvalidInputFileException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};