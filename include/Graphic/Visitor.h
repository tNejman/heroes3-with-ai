#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Visitor:
  - Klasa Visitor odpowiada za interfejs odwiedzania różnych obiektów w grze.
*/

#include <SFML/Graphics.hpp>

class Castle;
class Character;
class Building;
class WorldMap;
class Artifact;
class Obstacle;
class Spell;
class SpellBook;
class SecondarySkill;
class Resource;
class WarMachine;
class Player;
class Unit;
class Battle;
class OverworldObstacle;

class Visitor {
 public:
  // Do not make this virtual method: visit(const Terrain&)
  virtual sf::Texture& visit( const Artifact& e ) = 0;
  virtual sf::Texture& visit( const Obstacle& e ) = 0;
  virtual sf::Texture& visit( const Character& e ) = 0;
  virtual sf::Texture& visit( const SecondarySkill& e ) = 0;
  virtual sf::Texture& visit( const Spell& e ) = 0;
  // virtual sf::Texture& visit(const SpellBook& e) = 0;
  virtual sf::Texture& visit( const Unit& e ) = 0;
  virtual sf::Texture& visit( const Resource& e ) = 0;
  virtual sf::Texture& visit( const OverworldObstacle& e ) = 0;
  // virtual sf::Texture& visit(const Building& e) = 0;
  // virtual sf::Texture& visit(const WorldMap& e) = 0;
  // virtual sf::Texture& visit(const Player& e) = 0;
  // virtual sf::Texture& visit(const Castle& e) = 0;
  virtual sf::Texture& visit( const Battle& e ) = 0;
  virtual ~Visitor() = default;
};