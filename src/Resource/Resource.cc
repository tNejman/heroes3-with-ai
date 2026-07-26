#include "Resource/Resource.h"

std::string Resource::getName() const {
  switch ( resource_ ) {
    case availableResource::TIMBER:
      return "Timber";
    case availableResource::MERCURY:
      return "Mercury";
    case availableResource::STONE:
      return "Stone";
    case availableResource::SULFER:
      return "Sulfer";
    case availableResource::CRYSTAL:
      return "Crystal";
    case availableResource::GEMSTONE:
      return "Gemstone";
    case availableResource::MONEY:
      return "Money";
    default:
      return "";
  }
};