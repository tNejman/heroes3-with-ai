#pragma once

#include <cstddef>
#include <set>
#include <unordered_map>
#include <utility>

#include <SFML/Window/Keyboard.hpp>

using Chord = std::set<sf::Keyboard::Key>;

enum class ActionId {};

struct ChordHash {
  [[nodiscard]] size_t operator()( const Chord& c ) const noexcept {
    return ( size_t( c ) << 8 ) |
  }
}

using BindingTable = std::unordered_map<Chord, ActionId, ChordHash>;

namespace bindings {}  // namespace bindings

template <typename MoveType>
class IKeyboardHandler {
 private:
 public:
  void bind( Chord c, Action a ) noexcept {
    bindings_[c] = std::move( a );
  }
  [[nodiscard]] virtual MoveType monitorKeyPressesAndgetMove() noexcept = 0;
};