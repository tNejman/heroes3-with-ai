#pragma once
// Autor: Tomasz Naszkowski
// zawartość: klasa Resource pozwala na zarządzanie zasobami

class Resource {
 public:
  enum class Type : char { TIMBER, MERCURY, STONE, SULFUR, CRYSTAL, GEMSTONE, MONEY, COUNT };

 private:
  Type type_;
  int amount_;

 public:
  Resource() = delete;
  Resource( Type type, int amount ) noexcept;
  [[nodiscard]] Type getType() const noexcept;
  [[nodiscard]] int getAmount() const noexcept;
};