#pragma once

#include <exception>
#include <string>

class ObjectNotFoundException : public std::exception {
 private:
  std::string message;

 public:
  ObjectNotFoundException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};