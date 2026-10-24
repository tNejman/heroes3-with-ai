#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "engine/model/IGraphics/Visitor.h"
#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );
  void accept( Visitor& v ) const override;

  [[nodiscard]] std::string getName() const;
};