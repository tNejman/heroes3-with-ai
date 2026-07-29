#include "LoadAndSaveTools/MapSaver.h"

#include <fstream>

#include "Exceptions/_NotImplementedException.hpp"

void MapSaver::doSave( std::ofstream& out ) const {
  out << "hello" << std::endl;                          // placeholder, zeby kompilator sie nie czepial
  throw NotImplementedException( "MapSaver::doSave" );  // TODO zaimplementowac zapis mapy
}

// MapSaver::MapSaver( const std::string& path, const WorldMap& mapRef ) : ISaver( path ), map_( mapRef ) {};