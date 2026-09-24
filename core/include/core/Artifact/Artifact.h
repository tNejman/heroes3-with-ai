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

#include <functional>

#include "core/Artifact/ArtifactLib.h"

class Visitor;

// public Printable
class Artifact {
 private:
  std::reference_wrapper<const artifact::Data> data_;

  Artifact( const artifact::Data& data );

 public:
  Artifact() = delete;
  void accept( Visitor& ) const;

  [[nodiscard]] static Artifact create( artifact::Type type ) noexcept;
  [[nodiscard]] const artifact::Data& getData() const noexcept;
  [[nodiscard]] Artifact copy() const noexcept;

  bool operator==( const Artifact& other ) const noexcept;
};