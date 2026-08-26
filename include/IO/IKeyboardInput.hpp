
#include <SFML/Window/Keyboard.hpp>
#include <set>

#include "IO/KeyboardLib.h"
#include "Miscellaneous/ProjectLib.h"

struct IKeyboardInput {
  [[nodiscard]] virtual std::set<sf::Keyboard::Key> pressedNow() const = 0;
  virtual ~IKeyboardInput() = default;
};

struct RealKeyboardInput : public IKeyboardInput {
  [[nodiscard]] std::set<sf::Keyboard::Key> pressedNow() const override {
    std::set<sf::Keyboard::Key> keys;
    for ( const auto &key : MOVEMENT_KEYS ) {
      if ( sf::Keyboard::isKeyPressed( key ) ) {
        keys.insert( key );
      }
    }
    return keys;
  }
};

struct MockKeyboardInput : public IKeyboardInput {
  std::set<sf::Keyboard::Key> frame_;
  std::set<sf::Keyboard::Key> pressedNow() const override {
    return frame_;
  }
  void set( std::initializer_list<sf::Keyboard::Key> keys ) {
    frame_ = keys;
  }
};