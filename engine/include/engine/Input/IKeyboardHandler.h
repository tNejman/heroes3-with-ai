#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <set>
#include <unordered_map>

using Chord = std::set<sf::Keyboard::Key>;

enum class ActionId {};

struct ChordHash {
  size_t operator()(const Chord& c) const noexcept {
    return (size_t(c) << 8) | 
  }
}

using BindingTable = std::unordered_map<Chord, ActionId, ChordHash>;

namespace bindings {}  // namespace bindings

template <typename MoveType>
class IKeyboardHandler {
 private:
 public:
  void bind( Chord c, Action a ) {
    bindings_[c] = std::move( a );
  }
  virtual MoveType monitorKeyPressesAndgetMove() = 0;
};