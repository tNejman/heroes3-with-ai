#include "core/Resource/Resource.h"

#include "aux/Err.hpp"

Resource::Resource( Resource::Type type, int amount ) noexcept : type_( type ), amount_( amount ) {
  err::passCondOrAbort( amount_ >= 0, "resource amount needn't be negative" );
};

Resource::Type Resource::getType() const noexcept {
  return this->type_;
}

int Resource::getAmount() const noexcept {
  return this->amount_;
}