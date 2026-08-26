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

#include "Artifact/Artifact.h"
#include "Battle/Battle.h"
#include "Battle/Obstacle.hpp"
#include "Character/Character.h"
#include "Character/SecondarySkill.h"
#include "Graphics/Visitor.h"
#include "Magic/Spell.h"
#include "Resource/Resource.h"
#include "WorldMap/OverworldObstacle.h"

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