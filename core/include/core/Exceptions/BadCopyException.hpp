#pragma once

#include <exception>
#include <string>
#include <utility>

class BadCopyException : public std::exception {
 private:
  std::string message_;

 public:
  [[nodiscard]] constexpr BadCopyException( std::string msg ) noexcept : message_( std::move( msg ) ) {
  }

  [[nodiscard]] constexpr const char* what() const noexcept override {
    return message_.c_str();
  }
};