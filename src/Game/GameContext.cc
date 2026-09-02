#include "Game/GameContext.h"

#include <algorithm>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "Character/Character.h"
#include "Exceptions/Err.hpp"
#include "Miscellaneous/CycleEnumVal.hpp"
#include "Player/Player.h"

GameContext::GameContext( std::vector<std::shared_ptr<Player>>&& players ) noexcept
    // there must be at least 2 players
    // each player must have at least 1 character
    : players_( std::move( players ) ),
      current_player_( *( players_[0] ) ),
      current_character_( *( current_player_.get().getCharacters()[0] ) ) {
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

[[nodiscard]] const Player& GameContext::getCurrentPlayer() const noexcept {
  return current_player_;
}
[[nodiscard]] Player& GameContext::getCurrentPlayer() noexcept {
  return current_player_;
}
[[nodiscard]] const Character& GameContext::getCurrentCharacter() const noexcept {
  return current_character_;
}
[[nodiscard]] Character& GameContext::getCurrentCharacter() noexcept {
  return current_character_;
}

Player& GameContext::nextPlayer() noexcept {
  const PlayerColor current_player_color = current_player_.get().getColor();
  PlayerColor candidate = next( current_player_color );
  while ( candidate != current_player_color ) {
    const auto it =
        std::ranges::find_if( players_, [&]( const auto& player ) { return player->getColor() == candidate; } );
    if ( it != players_.end() ) {
      current_player_ = **it;
      return current_player_;
    }
    candidate = next( candidate );
  }
  err::abort( "no other player found" );
}

Character& GameContext::nextCharacter() noexcept {
  if ( current_player_.get().getCharacters().size() <= 1 ) {
    return current_character_;
  }
  const auto it = 1
                  + std::ranges::find_if( current_player_.get().getCharacters(),
                                          [&]( const std::shared_ptr<Character>& character ) {
                                            return character.get() == std::addressof( current_character_.get() );
                                          } );
  current_character_ = [&]() -> Character& {
    if ( it == current_player_.get().getCharacters().end() ) {
      return **( current_player_.get().getCharacters().begin() );
    }
    return **it;
  }();
  return current_character_;
}