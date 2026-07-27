#pragma once
// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'Artifact' implementuje obiekt artefaktu, który może być
        założony przez postać, czekający w plecaku, leżący na mapie
    - artefakt zawiera:
        - typ, a.k.a. nazwę
        - miejsce w ekwipunku na jakie może być założony
        - statystyki jakie przyznaje po założeniu
*/

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <cstddef>
#include <memory>
#include <string>

#include "MapObject/MapObject.h"
#include "Miscellaneous/ArtifactLib.h"
#include "Miscellaneous/Equippable.h"
#include "Miscellaneous/ProjectLib.h"

class Visitor;

// public Printable
class Artifact : public Equippable, public MapObject {
 private:
  std::shared_ptr<const ArtifactData> artifact_data_;

 public:
  Artifact() = delete;
  Artifact( std::shared_ptr<const ArtifactData> data );
  [[nodiscard]] static std::unique_ptr<Artifact> create( const ArtifactType type );

  [[nodiscard]] sf::Texture& accept( Visitor& vis ) const override;
  [[nodiscard]] ArtifactType getType() const;
  [[nodiscard]] EquipmentSlots getSlot() const;
  [[nodiscard]] const std::string& getName() const;
  [[nodiscard]] int getAttack() const;
  [[nodiscard]] int getDefense() const;
  [[nodiscard]] int getPower() const;
  [[nodiscard]] int getKnowledge() const;
  [[nodiscard]] int getSpeed() const;
  [[nodiscard]] size_t getCost() const;

  [[nodiscard]] std::unique_ptr<Artifact> copy() const;
};