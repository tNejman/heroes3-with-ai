#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "Graphics/Visitor.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );
  void accept( Visitor& v ) const override;

  [[nodiscard]] std::string getName() const;
};