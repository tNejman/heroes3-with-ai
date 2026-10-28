#include "core/Player/Player.h"

#include <memory>
#include <vector>

#include "core/Character/Character.h"

const std::vector<std::shared_ptr<Character>>& Player::getCharacters() const noexcept {
  return this->characters_on_map_;
}

std::vector<std::shared_ptr<Character>>& Player::getCharacters() noexcept {
  return this->characters_on_map_;
}

[[nodiscard]] PlayerColor Player::getColor() const noexcept {
  return color_;
}
