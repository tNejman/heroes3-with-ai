#pragma once

#include <fstream>
#include <string>

#include <json.hpp>

#include "aux/Err.hpp"

#include "core/Exceptions/DamagedSaveException.hpp"
#include "core/Exceptions/InvalidInputFileException.hpp"

using json = nlohmann::json;

template <typename TypeLoaded>
class IJsonLoader {
 protected:
  json data_;

  void load( const std::string& path ) noexcept {
    if ( !path.ends_with( ".json" ) ) {
      std::string message = "";
      message += typeid( TypeLoaded ).name();
      message += "-Loader Exptected to read json file but instead got: ";
      message += path;
      err::raise<InvalidInputFileException>( message );
    }
    std::ifstream file( path );
    data_ = json::parse( file );
  }
  [[nodiscard]] virtual std::shared_ptr<TypeLoaded> doGetObject() noexcept = 0;

 public:
  [[nodiscard]] IJsonLoader() noexcept = default;
  virtual ~IJsonLoader() noexcept = default;

  [[nodiscard]] std::shared_ptr<TypeLoaded> getObject() const noexcept {
    load();
    return doGetObject();
  }
};