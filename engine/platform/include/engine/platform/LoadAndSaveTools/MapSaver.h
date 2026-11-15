#pragma once

#include <fstream>
#include <string>

#include "engine/platform/LoadAndSaveTools/ISaver.hpp"

#include "core/WorldMap/WorldMap.h"

class MapSaver : public ISaver {
 private:
  // const WorldMap& map_;
  void doSave( std::ofstream& out ) const noexcept override;

 public:
  [[nodiscard]] MapSaver( const std::string& path, const WorldMap& mapRef ) noexcept;
};