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
#include <functional>

#include "Artifact/ArtifactLib.h"

class Visitor;

// public Printable
class Artifact {
 private:
  std::reference_wrapper<const ArtifactData> data_;

  Artifact( const ArtifactData& data );

 public:
  Artifact() = delete;
  [[nodiscard]] sf::Texture& accept( Visitor& vis ) const;

  [[nodiscard]] static Artifact create( const ArtifactType type ) noexcept;
  [[nodiscard]] const ArtifactData& getData() const noexcept;
  [[nodiscard]] Artifact copy() const noexcept;

  bool operator==( const Artifact& other ) const noexcept;
};