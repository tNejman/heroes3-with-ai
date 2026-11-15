#pragma once

#include <exception>
#include <string>
#include <utility>

class EmptySlotException : public std::exception {
 private:
  std::string message_;

 public:
  [[nodiscard]] constexpr EmptySlotException( std::string msg ) noexcept : message_( std::move( msg ) ) {
  }

  [[nodiscard]] constexpr const char* what() const noexcept override {
    return message_.c_str();
  }
};