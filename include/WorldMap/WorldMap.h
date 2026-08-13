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

// #include <SFML/Graphics.hpp>

#include <array>
#include <memory>
#include <vector>

#include "Character/Character.h"
#include "Game/IGameState.h"
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/OverworldObstacle.h"

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
  WorldMapGrid<std::shared_ptr<MapObject>> foreground_;

  std::vector<std::shared_ptr<Character>> characters_;
  std::vector<std::shared_ptr<Building>> buildings_;

  void loadBackground( const WorldMapGrid<int>& new_grid ) noexcept;
  void loadObstacles(
      std::vector<std::shared_ptr<OverworldObstacle>> obstacles ) noexcept;  // pass by value so it can bind to rvalue

 public:
  WorldMap() = delete;
  WorldMap( const WorldMapGrid<int>& new_grid ) noexcept;
  WorldMap( const WorldMapGrid<int>& new_grid, std::vector<std::shared_ptr<OverworldObstacle>> ) noexcept;

  [[nodiscard]] static bool areCoordsInBounds( CoordPair coords ) noexcept;

  [[nodiscard]] Terrain getTerrain( CoordPair coords ) const noexcept;

  [[nodiscard]] std::shared_ptr<MapObject>& getMapObjectShared( CoordPair coords ) noexcept;
  [[nodiscard]] const MapObject* getMapObject( CoordPair coords ) const noexcept;
  [[nodiscard]] MapObject* getMapObject( CoordPair coords ) noexcept;
  void setMapObject( CoordPair coords, std::shared_ptr<MapObject> object ) noexcept;
  void resetMapObject( CoordPair coords ) noexcept;
  [[nodiscard]] StateTransition moveMapObject( CoordPair old_coords, CoordPair new_coords );
};