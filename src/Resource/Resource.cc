#include "Resource/Resource.h"

#include "Graphics/Visitor.h"

Resource::Resource( ResourceType type, int amount ) : type_( type ), amount_( amount ) {};

void Resource::accept( Visitor& v ) const {
  v.visit( *this );
}

ResourceType Resource::getType() const noexcept {
  return this->type_;
}

int Resource::getAmount() const noexcept {
  return this->amount_;
}