#pragma once

#include <exception>
#include <string>

class ExpiredWeakPtrException : public std::exception {
 private:
  std::string message;

 public:
  ExpiredWeakPtrException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};