#include "LoadAndSaveTools/ISaver.h"

#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>

#include "Exceptions/Err.hpp"

bool ISaver::checkPath( const std::string& path ) {
  std::ofstream out( path, std::ios::app );
  if ( !out ) {
    return false;
  }
  out.close();
  return true;
}

ISaver::ISaver( const std::string& path ) {
  if ( checkPath( path ) ) {
    path_ = path;
  } else {
    err::raise<std::runtime_error>( "Failed to open file: " + path );
  }
}

void ISaver::save() {
  std::ofstream out( path_, std::ios::app );
  this->doSave( out );
  out.close();
}