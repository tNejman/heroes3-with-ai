#pragma once
// Autor: Tomasz Nejman

#include <string>

#include "core/MapObject/MapObject.h"
#include "engine/model/IGame/Coords.h"
#include "engine/model/IGraphics/Visitor.h"

class Building : public MapObject {
 private:
  std::string name_;

 public:
  Building( CoordPair coords, std::string name );
  void accept( Visitor& v ) const override;

  [[nodiscard]] std::string getName() const;
};