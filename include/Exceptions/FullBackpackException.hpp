#pragma once
#include <exception>
#include <string>

class FullBackpackException : public std::exception {
 private:
  std::string message;

 public:
  FullBackpackException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};