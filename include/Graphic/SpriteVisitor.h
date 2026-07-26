#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy SpriteVisitor:
  - Klasa SpriteVisitor odpowiada za odwiedzanie różnych obiektów w grze i zwracanie odpowiednich tekstur.
  - Używa wzorca projektowego Visitor do oddzielenia logiki odwiedzania obiektów od ich implementacji.
  - Zawiera metody do odwiedzania różnych typów obiektów.
  - Każda metoda zwraca odpowiednią teksturę dla danego obiektu.
*/
#include <stdint.h>

#include <algorithm>
#include <array>
#include <memory>
#include <string>

#include "Artifacts/Artifact.h"
#include "Battle/Battle.h"
#include "Battle/Obstacle.h"
#include "Characters/Character.h"
#include "Characters/SecondarySkill.h"
#include "Magic/Spell.h"
#include "Miscellaneous/ProjectLib.h"
#include "SFML/Graphics.hpp"
// #include "Magic/SpellBook.h"
#include "Resource/Resource.h"
#include "Units/Unit.h"
// #include "WorldMap/Building.h"
// #include "WorldMap/WorldMap.h"
// #include "Player/Player.h"
// #include "WorldMap/Castles/Castle.h"
#include "Battle/Moves/MoveFactory.h"
#include "Exceptions/BadCopyException.hpp"
#include "Exceptions/InvalidTextureException.hpp"
#include "Graphic/Visitor.h"
#include "WorldMap/OverworldObstacle.h"

class SpriteVisitor : public Visitor {
 public:
  SpriteVisitor() = default;
  sf::Texture& visit( const Artifact& e ) override;
  sf::Texture& visit( const Obstacle& e ) override;
  sf::Texture& visit( const Character& e ) override;
  sf::Texture& visit( const SecondarySkill& e ) override;
  sf::Texture& visit( const Spell& e ) override;
  // sf::Texture& visit(const SpellBook& e) override;
  sf::Texture& visit( const Unit& e ) override;
  sf::Texture& visit( const Resource& e ) override;
  sf::Texture& visit( const OverworldObstacle& e ) override;
  // sf::Texture& visit(const Building& e) override;
  sf::Texture& visit( const Terrain& e );
  // sf::Texture& visit(const WorldMap& e) override;
  // sf::Texture& visit(const Player& e) override;
  // sf::Texture& visit(const Castle& e) override;
  sf::Texture& visit( const Battle& e ) override;
  std::pair<sf::Texture&, std::string> getBattleHexagons( std::vector<std::shared_ptr<Move>> moves );

 private:
  std::map<std::string, sf::Texture> textures_;
  sf::Texture& FindTexture( const std::string& path );
  sf::Image mirrorImageHorizontally( const sf::Image& original ) const;
};