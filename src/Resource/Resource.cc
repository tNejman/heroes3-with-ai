#include "Resource/Resource.h"

#include <string>

const std::string& Resource::getName() const noexcept {
  static const std::string empty = "";
  static const std::string timber = "Timber";
  static const std::string mercury = "Mercury";
  static const std::string stone = "Stone";
  static const std::string sulfer = "Sulfer";
  static const std::string crystal = "Crystal";
  static const std::string gemstone = "Gemstone";
  static const std::string money = "Money";

  switch ( resource_ ) {
    case availableResource::TIMBER: return timber;
    case availableResource::MERCURY: return mercury;
    case availableResource::STONE: return stone;
    case availableResource::SULFER: return sulfer;
    case availableResource::CRYSTAL: return crystal;
    case availableResource::GEMSTONE: return gemstone;
    case availableResource::MONEY: return money;
    default: return empty;
  }
}