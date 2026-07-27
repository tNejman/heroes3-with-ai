#pragma once

#include <fstream>
#include <json.hpp>
#include <string>

#include "Exceptions/DamagedSaveException.hpp"
#include "Exceptions/InvalidInputFileException.hpp"

using json = nlohmann::json;

template <typename TypeLoaded>
class IJsonLoader {
 protected:
  json data_;

  void load( const std::string& path ) {
    if ( !path.ends_with( ".json" ) ) {
      std::string message = "";
      message += typeid( TypeLoaded ).name();
      message += "-Loader Exptected to read json file but instead got: ";
      message += path;
      throw InvalidInputFileException( message );
    }
    std::ifstream file( path );
    data_ = json::parse( file );
  }
  virtual std::shared_ptr<TypeLoaded> doGetObject() = 0;

 public:
  IJsonLoader() = default;
  virtual ~IJsonLoader() = default;

  std::shared_ptr<TypeLoaded> getObject() const {
    load();
    return doGetObject();
  }
};