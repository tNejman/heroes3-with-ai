#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy Visitor:
  - Klasa Visitor odpowiada za interfejs odwiedzania różnych obiektów w grze.
*/

#include "aux/Visitor.hpp"

class Artifact;
class Character;
class Obstacle;
class OverworldObstacle;
class UnitStack;

using GfxVisitor = visitor::Visitor<Artifact, Obstacle, Character, OverworldObstacle, UnitStack>;