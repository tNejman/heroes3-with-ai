#include "Player/Player.h"

std::vector<std::shared_ptr<Character>>& Player::getCharacters() {
  return this->characters_on_map_;
}