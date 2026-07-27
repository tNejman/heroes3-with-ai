#include "LoadAndSaveTools/ISaver.h"

bool ISaver::checkPath( const std::string& path ) {
  std::ofstream out( path, std::ios::app );
  if ( !out ) return false;
  out.close();
  return true;
}

ISaver::ISaver( const std::string& path ) {
  if ( checkPath( path ) )
    path_ = path;
  else
    throw std::runtime_error( "Failed to open file: " + path );
}

void ISaver::save() {
  std::ofstream out( path_, std::ios::app );
  this->doSave( out );
  out.close();
}