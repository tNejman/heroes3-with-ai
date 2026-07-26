#pragma once

#include "LoadAndSaveTools/ISaver.hpp"
#include "WorldMap/WorldMap.h"

class MapSaver : public ISaver {
 private:
  const WorldMap& map_;
  void doSave( std::ofstream& out ) const override;

 public:
  MapSaver( const std::string& path, const WorldMap& mapRef );
};