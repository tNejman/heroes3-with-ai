#pragma once

#include <fstream>
#include <string>

class ISaver {
 private:
  std::string path_;

  [[nodiscard]] bool checkPath( const std::string& path ) const noexcept;
  virtual void doSave( std::ofstream& out ) const noexcept = 0;

 public:
  ISaver() = delete;
  [[nodiscard]] ISaver( const std::string& path ) noexcept;
  virtual ~ISaver() noexcept = default;

  void save() noexcept;
};