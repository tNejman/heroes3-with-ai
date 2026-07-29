#include "Resource/Resource.h"

#include <SFML/Graphics/Texture.hpp>

#include "Graphics/Visitor.h"

Resource::Resource( ResourceType type, int amount ) : type_( type ), amount_( amount ) {};

sf::Texture& Resource::accept( Visitor& v ) const {
  return v.visit( *this );
}

ResourceType Resource::getType() const noexcept {
  return this->type_;
}

int Resource::getAmount() const noexcept {
  return this->amount_;
}