#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'Move' implementuje obiekt ruchu, który może wykonać gracz w swojej turze podczas bitwy
    - każda klasa dziedzicząca po 'Move' na swój sposób implementuje metodę execute()
*/

#include <memory>
#include <string>

#include "Miscellaneous/Coords.h"

class Battle;

class Move {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~Move() = default;
  virtual void execute( std::shared_ptr<Battle> battle ) = 0;
  [[nodiscard]] virtual std::string getInfo( std::shared_ptr<Battle> battle ) const = 0;
  [[nodiscard]] virtual CoordPair destinationCoords() const = 0;
  [[nodiscard]] virtual std::string getPath() const = 0;
  [[nodiscard]] virtual std::shared_ptr<Move> copy() const = 0;
};
