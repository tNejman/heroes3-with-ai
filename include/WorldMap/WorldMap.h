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
#include "MapObject/MapObject.h"
#include "Miscellaneous/Coords.h"
#include "Miscellaneous/ProjectLib.h"
#include "WorldMap/GridTile.h"
#include "WorldMap/OverworldObstacle.h"

class Character;
class Building;

class WorldMap {
 private:
  std::array<std::array<std::shared_ptr<GridTile>, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>
      grid_;  // underlying map structure
  std::vector<std::shared_ptr<Character>> characters_;
  std::vector<std::shared_ptr<Building>> buildings_;

  void loadGrid( std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& new_grid );
  [[nodiscard]] bool getIfCoordsInBounds( CoordPair coords ) const;
  [[nodiscard]] bool getIfCoordsInBounds( CoordPair coords, ShiftPair shift ) const;
  //  uint32_t calculateTravelCost(const std::string& character_name, const CoordPair destination_coords);

 public:
  WorldMap() = delete;
  WorldMap( std::array<std::array<int, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& new_grid );
  void loadObstacles( std::vector<std::shared_ptr<OverworldObstacle>>& obstacels );
  // std::array<std::array<std::shared_ptr<GridTile>, WORLD_MAP_WIDTH>, WORLD_MAP_HEIGHT> getGridTransposed();

  void setMapObject( CoordPair coords, std::shared_ptr<MapObject> object );
  void moveMapObject( CoordPair old_coords, CoordPair new_coords );
  void moveMapObject( CoordPair old_coords, ShiftPair shift );

  [[nodiscard]] std::shared_ptr<GridTile> getTile( CoordPair coords ) const;
  [[nodiscard]] std::shared_ptr<GridTile> getTile( CoordPair coords );

  //  sf::Texture& accept(Visitor& v) const { return v.visit(*this); }
  //  std::array<std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& getGrid() const;
  //  std::array<std::unique_ptr<GridTile>, WORLD_MAP_WIDTH>& getRow( const uint32_t row_num ) const;
  //  std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>& getColumn( const uint32_t column_num ) const;
  //  std::shared_ptr<MapObject>& getObject( const CoordPair coords ) const;
  //  std::shared_ptr<MapObject>& getObject( const std::unique_ptr<GridTile>& base_tile ) const;

  //  uint32_t getTileXCoord( const std::unique_ptr<GridTile>& tile ) const;
  //  uint32_t getTileYCoord( const std::unique_ptr<GridTile>& tile ) const;

  //  uint32_t getObjectXCoord( const std::unique_ptr<MapObject>& object ) const;
  //  uint32_t getObjectYCoord( const std::unique_ptr<MapObject>& object ) const;

  //  std::vector<std::unique_ptr<Character>>& getCharacters() const;
  //  uint32_t getCharacterXCoord( const std::string& character_name ) const;
  //  uint32_t getCharacterYCoord( const std::string& character_name ) const;

  //  std::vector<std::unique_ptr<Building>>& getBuildings() const;
  //  uint32_t getBuildingXCoord( const std::string& building_name ) const;
  //  uint32_t getBuildingYCoord( const std::string& building_name ) const;

  //  void setGrid( std::array<std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>, WORLD_MAP_WIDTH>& new_grid );
  //  void setRow( std::array<std::unique_ptr<GridTile>, WORLD_MAP_WIDTH>& new_row );
  //  void setColumn( std::array<std::unique_ptr<GridTile>, WORLD_MAP_HEIGHT>& new_column );
  //  void setTile( std::unique_ptr<GridTile>& new_tile );
  //  void setTile( const std::unique_ptr<GridTile>& tile, const uint32_t x_coord, const uint32_t y_coord );
  //  void swapTiles( const CoordPair coords_a, const CoordPair coords_b );

  //  void setMapObject( std::unique_ptr<MapObject>& map_object, std::unique_ptr<GridTile>& grid_tile );
  //  void setMapObject( std::unique_ptr<MapObject>& map_object, const CoordPair coords );
  //  void swapMapObjects( const CoordPair coords_a, const CoordPair coords_b );

  //  void addCharacter( const std::shared_ptr<Character>& character );
  //  void removeCharacter( const std::string& character_name );
  //  void removeCharacters();

  //  void addBuilding( const std::unique_ptr<Building>& building );
  //  void removeBuilding( const std::string& building_name );
  //  void removeBuildings();

  //    std::vector<std::shared_ptr<GridObject>>&

  //    std::vector<std::shared_ptr<Character>>& findNeighbours(uint32_t zasięg);
};