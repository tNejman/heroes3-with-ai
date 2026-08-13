#pragma once

#include <cassert>
#include <cstdint>
#include <memory>
#include <vector>

#include "LoadAndSaveTools/ILoader.hpp"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"
#include "WorldMap/WorldMap.h"
/**
 * @brief
 * This class performs an operation of loading a .txt file,
 * parsing it and creating an instance of WorldMap,
 * based on file parsed; turns 0,1,2,etc. to Terrain using enum from ProjectLib.
 *
 * @details
 * @param y_counter starts from WORLD_MAP_HEIGHT - 1 and not 0, because the .txt file is parsed
 * from top to bottom, so to keep the same orientation of the file and the map visual,
 * MapLoader iterates through WorldMap grid in reverse order vertically.
 *
 * In getObjectFromContainer() y_counter_ is asserted to have
 * the value of 4'294'967'295 because it is decremented one too many times,
 * which causes the value to turn from 0 to uint32_t.max_val
 */
class MapLoader : public ILoader<WorldMap, WorldMapGrid<int>> {
 private:
  uint32_t x_counter_ = 0;
  uint32_t y_counter_ = WORLD_MAP_HEIGHT - 1;

  void resetCounters() override;
  void moveWordToContainer( int word ) override;
  [[nodiscard]] WorldMap getObjectFromContainer() override;

  [[nodiscard]] static std::vector<std::shared_ptr<OverworldObstacle>> generateObstacles();

 public:
};