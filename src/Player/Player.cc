#include "Player/Player.h"

#include <memory>
#include <vector>

#include "Character/Character.h"


std::vector<std::shared_ptr<Character>>& Player::getCharacters() noexcept {
  return this->characters_on_map_;
}