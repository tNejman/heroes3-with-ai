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

#include <stdint.h>

#include <array>
#include <memory>
#include <string>

#include "Exceptions/InvalidArtifactTypeException.hpp"
#include "Miscellaneous/ArtifactLib.h"
#include "Miscellaneous/Equippable.h"
#include "Miscellaneous/Printable.h"
#include "WorldMap/MapObject.h"

// public Printable
class Artifact : public Equippable, public MapObject {
 private:
  const std::shared_ptr<const ArtifactData> artifact_data_;

 public:
  // @Warning artifact cannot possibly have default constructor, for
  // artifact data is quintesential to its
  // Artifact() = default;
  Artifact( const std::shared_ptr<const ArtifactData>& data );
  static std::unique_ptr<Artifact> create( const ArtifactType type );

  sf::Texture& accept( Visitor& v ) const;  // override
  ArtifactType getType() const;
  EquipmentSlots getSlot() const;
  const std::string& getName() const;
  int getAttack() const;
  int getDefense() const;
  int getPower() const;
  int getKnowledge() const;
  int getSpeed() const;
  size_t getCost() const;

  std::unique_ptr<Artifact> copy() const;
};