#include "Game/GameContext.h"

#include <memory>
#include <utility>
#include <vector>

#include "Character/Character.h"
#include "Player/Player.h"

GameContext::GameContext( std::vector<std::shared_ptr<Player>>&& players ) noexcept : players_( std::move( players ) ) {
}

[[nodiscard]] const std::vector<std::shared_ptr<Player>>& GameContext::getPlayers() const noexcept {
  return players_;
}
[[nodiscard]] std::vector<std::shared_ptr<Player>>& GameContext::getPlayers() noexcept {
  return players_;
}

[[nodiscard]] std::shared_ptr<Character> GameContext::findCharacterById( int id ) const noexcept {
  for ( const auto& player : players_ ) {
    for ( const auto& character : player->getCharacters() ) {
      if ( character->getId() == id ) {
        return character;
      }
    }
  }
  return nullptr;
}
[[nodiscard]] std::shared_ptr<Character> GameContext::findCharacterById( int id ) noexcept {
  return std::as_const( *this ).findCharacterById( id );
}