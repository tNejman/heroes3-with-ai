#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Visitor:
  - Klasa Visitor odpowiada za interfejs odwiedzania różnych obiektów w grze.
*/

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
class UnitStack;
class Battle;
class OverworldObstacle;

class Visitor {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~Visitor() = default;
  virtual void visit( const Artifact& ) = 0;
  virtual void visit( const Obstacle& ) = 0;
  virtual void visit( const Character& ) = 0;
  virtual void visit( const SecondarySkill& ) = 0;
  virtual void visit( const Spell& ) = 0;
  virtual void visit( const Resource& ) = 0;
  virtual void visit( const OverworldObstacle& ) = 0;
  virtual void visit( const Building& ) = 0;
  virtual void visit( const UnitStack& ) = 0;
};