#include "core/Game/Context.h"

#include <algorithm>
#include <memory>
#include <utility>
#include <vector>

#include "aux/CycleEnumVal.hpp"
#include "aux/Err.hpp"
#include "core/Character/Character.h"
#include "core/Player/Player.h"

game::Context::Context( std::vector<std::shared_ptr<Player>>&& players ) noexcept
    // there must be at least 2 players
    // each player must have at least 1 character
    : players_( std::move( players ) ),
      current_player_( *( players_[0] ) ),
      current_character_( *( current_player_.get().getCharacters()[0] ) ) {
}

[[nodiscard]] const std::vector<std::shared_ptr<Player>>& game::Context::getPlayers() const noexcept {
  return players_;
}
[[nodiscard]] std::vector<std::shared_ptr<Player>>& game::Context::getPlayers() noexcept {
  return players_;
}

[[nodiscard]] std::shared_ptr<Character> game::Context::findCharacterById( int id ) const noexcept {
  for ( const auto& player : players_ ) {
    for ( const auto& character : player->getCharacters() ) {
      if ( character->getId() == id ) {
        return character;
      }
    }
  }
  return nullptr;
}
[[nodiscard]] std::shared_ptr<Character> game::Context::findCharacterById( int id ) noexcept {
  return std::as_const( *this ).findCharacterById( id );
}

[[nodiscard]] const Player& game::Context::getCurrentPlayer() const noexcept {
  return current_player_;
}
[[nodiscard]] Player& game::Context::getCurrentPlayer() noexcept {
  return current_player_;
}
[[nodiscard]] const Character& game::Context::getCurrentCharacter() const noexcept {
  return current_character_;
}
[[nodiscard]] Character& game::Context::getCurrentCharacter() noexcept {
  return current_character_;
}

Player& game::Context::nextPlayer() noexcept {
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

Character& game::Context::nextCharacter() noexcept {
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