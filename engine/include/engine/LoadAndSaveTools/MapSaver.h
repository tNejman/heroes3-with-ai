#pragma once

#include <fstream>
#include <string>

#include "engine/LoadAndSaveTools/ISaver.hpp"
#include "core/WorldMap/WorldMap.h"

class MapSaver : public ISaver {
 private:
  // const WorldMap& map_;
  void doSave( std::ofstream& out ) const override;

 public:
  MapSaver( const std::string& path, const WorldMap& mapRef );
};