#pragma once

#include <array>
// chorno is required for this to work: stringstream::operator>>(const std::string& str)
#include <chrono>
#include <fstream>
#include <string>

#include "Exceptions/InvalidInputFileException.hpp"
#include "Miscellaneous/ProjectLib.h"

template <typename T1, typename T2>
class ILoader {
 protected:
  T2 container_;

  virtual void resetCounters() = 0;
  virtual void moveWordToContainer( const int& word ) = 0;
  virtual std::shared_ptr<T1> getObjectFromContainer() = 0;

  bool isDigit( const std::string& s ) const {
    if ( s.length() != 1 ) {
      return false;
    }
    return std::isdigit( s[0] );
  }

 public:
  ILoader() {}
  virtual ~ILoader() = default;

  std::shared_ptr<T1> load( const std::string& path ) {
    resetCounters();
    std::ifstream file( path );
    if ( !file.is_open() ) {
      throw InvalidInputFileException( "Could not open file with WorldMap data; path:" + path );
    }

    std::string line;
    while ( std::getline( file, line ) ) {
      std::stringstream ss( line );
      std::string word;

      while ( ss >> word ) {
        // while ( word = ss.str() ) {
        if ( !isDigit( word ) ) {
          throw InvalidInputFileException( "Invalid characters in WorldMap input file" );
        }
        const int word_int = std::stoi( word );
        moveWordToContainer( word_int );
      }
    }
    file.close();
    return getObjectFromContainer();
  }
};