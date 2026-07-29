
#include <SFML/Window/Keyboard.hpp>
#include <set>

#include "Miscellaneous/ProjectLib.h"

struct IKeyboardInput {
  virtual std::set<sf::Keyboard::Key> pressedNow() const = 0;
  virtual ~IKeyboardInput() = default;
};

struct RealKeyboardInput : public IKeyboardInput {
  std::set<sf::Keyboard::Key> pressedNow() const override {
    std::set<sf::Keyboard::Key> keys;
    for ( auto &key : MOVEMENT_KEYS ) {
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