#pragma once
// Autor: Tomasz Nejman
/* zawartość:
    - klasa 'WorldMap' implementuje mapę po której może poruszać się bohater
    - znajdują się na niej:
      - postacie
      - jednostki
      - budynki (w tym zamki)
      - teren
*/

#include <array>
#include <memory>
#include <vector>

#include "core/Character/Character.h"
#include "core/Game/IState.h"
#include "core/MapObject/MapObject.h"
#include "core/Misc/ProjectLib.h"
#include "core/WorldMap/OverworldObstacle.h"
#include "engine/model/IGame/Coords.h"

#define COORDS_IN_BOUNDS_OR_THROW( coords, ... )        \
  err::passCondOrThrow<CoordinateOutOfBoundsException>( \
      WorldMap::areCoordsInBounds( coords ) __VA_OPT__(, ) __VA_ARGS__, coords );

class Character;
class Building;

template <typename TileInGrid>
using WorldMapGrid = std::array<std::array<TileInGrid, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>;

class WorldMap {
 private:
  WorldMapGrid<Terrain> background_;
  WorldMapGrid<MapObject*> foreground_;

  std::vector<Character*> character_;
  std::vector<std::unique_ptr<OverworldObstacle>> obstacles_;

  std::vector<std::shared_ptr<Building>> buildings_;

  void loadBackground( const WorldMapGrid<int>& new_grid ) noexcept;
  void loadObstacles( std::vector<std::unique_ptr<OverworldObstacle>>& obstacles ) noexcept;

 public:
  WorldMap() = delete;
  WorldMap( const WorldMapGrid<int>& new_grid ) noexcept;
  WorldMap( const WorldMapGrid<int>& new_grid, const std::vector<std::shared_ptr<OverworldObstacle>>& ) noexcept;

  [[nodiscard]] static bool areCoordsInBounds( CoordPair coords ) noexcept;

  [[nodiscard]] Terrain getTerrain( CoordPair coords ) const noexcept;

  [[nodiscard]] const MapObject* getMapObject( CoordPair coords ) const noexcept;
  [[nodiscard]] MapObject* getMapObject( CoordPair coords ) noexcept;
  void setMapObject( CoordPair coords, MapObject* object ) noexcept;
  void resetMapObject( CoordPair coords ) noexcept;
  [[nodiscard]] game::StateTransition moveMapObject( CoordPair old_coords, CoordPair new_coords );
};