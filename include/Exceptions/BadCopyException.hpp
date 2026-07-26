#pragma once

#include <exception>
#include <string>

class BadCopyException : public std::exception {
 private:
  std::string message;

 public:
  BadCopyException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};