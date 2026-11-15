#pragma once
// Autor: Tomasz Naszkowski
/* Zawartość klasy BattleField:
  - Klasa BattleField odpowiada za zarządzanie polem bitwy, w tym za przesuwanie jednostek,
  - dodawanie przeszkód i sprawdzanie, czy jednostka może dojść gdzieś.
  - Pole bitwy jest reprezentowane jako graf gdzie można poruszać się w 6 kierunkach.
*/

#include <array>
#include <memory>
#include <vector>

#include "engine/model/IGame/Coords.h"

#include "core/Misc/ProjectLib.h"

class Tile;
class GridTile;

using BattleGrid = std::array<std::array<std::shared_ptr<Tile>, MAP_HEIGHT_BF>, MAP_WIDTH_BF>;

class BattleField {
 private:
  BattleGrid battle_grid_;
  // battle_grid[width][height]
  Terrain background_;

 public:
  [[nodiscard]] BattleField( Terrain background );

  [[nodiscard]] const BattleGrid& getGrid() const noexcept;

  [[nodiscard]] std::vector<std::shared_ptr<Tile>> getTileNeighbours( CoordPair coords ) noexcept;
  [[nodiscard]] std::vector<std::shared_ptr<Tile>> getTileNeighbours( const std::shared_ptr<Tile>& tile ) noexcept;
  [[nodiscard]] std::shared_ptr<Tile> getTileByProxy( CoordPair coords ) noexcept;
  // int createRandomObstacles( int amount );         // TODO
  [[nodiscard]] static std::vector<CoordPair> getCoordPairs( CoordPair coords ) noexcept;

  [[nodiscard]] Terrain getBackground() const noexcept;

  // @Warning do not use method getBattleGrid(); the only safe access to tiles i via getTileByProxy()
  // std::array<std::array<std::shared_ptr<Tile>, MAP_HEIGHT_BF>, MAP_WIDTH_BF>& getBattleGrid() = delete;
  void eraseEmptyTiles();
};