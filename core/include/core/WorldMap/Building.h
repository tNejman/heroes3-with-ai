#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "engine/Graphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "core/Misc/Coords.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );
  void accept( Visitor& v ) const override;

  [[nodiscard]] std::string getName() const;
};