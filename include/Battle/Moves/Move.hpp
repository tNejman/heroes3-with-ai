#pragma once

// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'Move' implementuje obiekt ruchu, który może wykonać gracz w swojej turze podczas bitwy
    - każda klasa dziedzicząca po 'Move' na swój sposób implementuje metodę execute()
*/

#include <memory>
#include <string>

#include "Miscellaneous/ProjectLib.h"
class Battle;

class Move {
 public:
  Move() {};
  virtual ~Move() = default;
  virtual void execute( std::shared_ptr<Battle> battle ) = 0;
  virtual std::string getInfo( std::shared_ptr<Battle> battle ) const = 0;
  virtual CoordPair destinationCoords() const = 0;
  virtual std::string getPath() const = 0;
  virtual std::shared_ptr<Move> copy() const = 0;
};
