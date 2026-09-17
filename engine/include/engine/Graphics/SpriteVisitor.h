#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy SpriteVisitor:
  - Klasa SpriteVisitor odpowiada za odwiedzanie różnych obiektów w grze i zwracanie odpowiednich tekstur.
  - Używa wzorca projektowego Visitor do oddzielenia logiki odwiedzania obiektów od ich implementacji.
  - Zawiera metody do odwiedzania różnych typów obiektów.
  - Każda metoda zwraca odpowiednią teksturę dla danego obiektu.
*/

#include <SFML/Graphics/Sprite.hpp>
#include <optional>

#include "core/Artifact/Artifact.h"
#include "core/Battle/Battle.h"
#include "core/Battle/Obstacle.hpp"
#include "core/Character/Character.h"
#include "core/Character/SecondarySkill.h"
#include "engine/Graphics/Visitor.h"
#include "core/Magic/Spell.h"
#include "core/Resource/Resource.h"
#include "core/WorldMap/OverworldObstacle.h"

class SpriteVisitor : public Visitor {
 private:
  std::optional<sf::Sprite> sprite_;

 public:
  void visit( const Artifact& e ) override;
  void visit( const Obstacle& e ) override;
  void visit( const Character& e ) override;
  void visit( const SecondarySkill& e ) override;
  void visit( const Spell& e ) override;
  void visit( const Resource& e ) override;
  void visit( const OverworldObstacle& e ) override;
  void visit( const Building& e ) override;
  void visit( const UnitStack& e ) override;

  sf::Sprite extractSprite() noexcept;
};