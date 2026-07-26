#pragma once

#include <exception>
#include <string>

class TileNotFoundException : public std::exception {
 private:
  std::string message;

 public:
  TileNotFoundException( const std::string& msg ) : message( msg ) {}

  const char* what() const noexcept override {
    return message.c_str();
  }
};