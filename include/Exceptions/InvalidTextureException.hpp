#pragma once

#include <exception>
#include <string>

class InvalidTextureException : public std::exception {
 private:
  std::string message;

 public:
  InvalidTextureException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};