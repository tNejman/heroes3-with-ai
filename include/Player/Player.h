#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Player:
    - klasa pozwala na zarządzanie graczem
    - Jest też Interfejsem do zarządzania ruchami AI i człowieka
*/
// #include <SFML/Graphics.hpp>

#include <array>
#include <memory>
#include <vector>

#include "Characters/Character.h"
#include "Miscellaneous/Printable.h"
#include "Miscellaneous/ProjectLib.h"
#include "Resource/Resource.h"
#include "WorldMap/Castles/Castle.h"
class Move;

enum Color { RED,
             BLUE };

// inheritance from Printable is postponed for now
class Player {
 private:
  std::vector<std::shared_ptr<Character>> characters_on_map_;
  std::vector<std::weak_ptr<Castle>> owned_castles_;
  std::array<std::unique_ptr<Resource>, AMOUNT_OF_RESOURCES> Resources_;

 public:
  Player( std::vector<std::shared_ptr<Character>> characters ) : characters_on_map_( characters ) {}
  ~Player() = default;

  Color color_;

  std::vector<std::shared_ptr<Character>>& getCharacters();

  // below are not implemented
  bool addCharacter( std::shared_ptr<Character> character );
  void addCastle( std::shared_ptr<Castle> castle );
  std::shared_ptr<Castle> getCastles();
  bool deleteCharacter( std::shared_ptr<Character> character );
  bool loseCastle( std::shared_ptr<Castle> castle );
  std::array<std::shared_ptr<Resource>, AMOUNT_OF_RESOURCES> getResourcesInPointers();
  std::array<Resource, AMOUNT_OF_RESOURCES> getResourcesInValues();
  Resource getResource( availableResource Resource );
  Resource setResource( availableResource Resource, int amount );
  std::shared_ptr<Move> MakeMove( std::vector<Move> PossibleStates );
  // virtual sf::Texture& accept(Visitor& v) const override {return v.visit(*this); }
};