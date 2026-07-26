#pragma once
#include <exception>
#include <string>

class InvalidArtifactTypeException : public std::exception {
 private:
  std::string message;

 public:
  InvalidArtifactTypeException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};