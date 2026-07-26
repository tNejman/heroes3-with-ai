#pragma once

#include <fstream>
#include <string>

class ISaver {
 private:
  std::string path_;

  bool checkPath( const std::string& path ) {
    std::ofstream out( path );
    if ( !out )
      return false;
    out.close();
    return true;
  }

  virtual void doSave( std::ofstream& out ) const = 0;

 public:
  ISaver() = delete;
  ISaver( const std::string& path ) {
    if ( checkPath( path ) )
      path_ = path;
    else
      throw std::runtime_error( "Failed to open file: " + path );
  }
  virtual ~ISaver() = default;

  void save() {
    std::ofstream out( path_ );
    this->doSave( out );
    out.close();
  };
};