#pragma once

#include <cctype>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

#include "Exceptions/DamagedSaveException.hpp"
#include "Exceptions/InvalidInputFileException.hpp"

template <typename TypeLoaded, typename TypeContainer>
class ILoader {
 protected:
  TypeContainer container_;

  virtual void resetCounters() = 0;
  virtual void moveWordToContainer( const int word ) = 0;
  virtual std::shared_ptr<TypeLoaded> getObjectFromContainer() = 0;

  [[nodiscard]] bool isNumber( const std::string& s ) const {
    return !s.empty()
           && std::find_if( s.begin(), s.end(), []( unsigned char c ) { return !std::isdigit( c ); } ) == s.end();
  }

 public:
  ILoader() = default;
  ILoader( const ILoader& ) = delete;
  ILoader( ILoader&& ) = delete;
  ILoader& operator=( const ILoader& ) = delete;
  ILoader& operator=( ILoader&& ) = delete;
  explicit ILoader( TypeContainer container ) : container_( std::move( container ) ) {
  }
  virtual ~ILoader() = default;

  std::shared_ptr<TypeLoaded> load( const std::string& path ) {
    resetCounters();
    std::ifstream file( path );
    if ( !file.is_open() ) {
      throw InvalidInputFileException( "ILoader::load -> could not open file with data; path=" + path );
    }

    std::string line;
    while ( std::getline( file, line ) ) {
      std::stringstream ss( line );
      std::string word;

      while ( ss >> word ) {
        // while ( word = ss.str() ) {
        if ( !isNumber( word ) ) {
          throw InvalidInputFileException( "ILoader::load -> Invalid character in input file is not a number: " + word );
        }
        const int word_int = std::stoi( word );
        moveWordToContainer( word_int );
      }
    }
    file.close();
    return getObjectFromContainer();
  }
};