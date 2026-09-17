#pragma once

#include <fstream>
#include <string>

class ISaver {
 private:
  std::string path_;

  bool checkPath( const std::string& path );
  virtual void doSave( std::ofstream& out ) const = 0;

 public:
  ISaver() = delete;
  ISaver( const std::string& path );
  virtual ~ISaver() = default;

  void save();
};