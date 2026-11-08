#pragma once

#include "aux/HasMethod.hpp"

namespace visitor {

template <typename T>
class VisitorFor {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  virtual ~VisitorFor() = default;
  virtual void visit( const T& node ) noexcept = 0;
};

template <typename Derived, typename Base, typename... Ts>
class VisitorImpl;

template <typename... Ts>
class Visitor : public VisitorFor<Ts>... {
 public:
  using VisitorFor<Ts>::visit...;

  template <typename DerivedFromThis>
  using Impl = VisitorImpl<DerivedFromThis, Visitor, Ts...>;
};

template <typename Derived, typename Base>
class VisitorImpl<Derived, Base> : public Base {
 public:
  using Base::visit;
};

template <typename DerivedFromThis, typename Base, typename T, typename... Ts>
requires hasMethod_c<DerivedFromThis, "handleVisit">
class VisitorImpl<DerivedFromThis, Base, T, Ts...> : public VisitorImpl<DerivedFromThis, Base, Ts...> {
 public:
  using VisitorImpl<DerivedFromThis, Base, Ts...>::visit;

  void visit( const T& t ) noexcept override {
    this->handleVisit( t );
  }
};

template <typename DerivedFromThis, typename CommonInterface, typename CommonVisitor>
class Visitable : public CommonInterface {
 public:
  void accept( CommonVisitor& visitor ) const noexcept override {
    visitor.visit( static_cast<const DerivedFromThis&>( *this ) );
  }
};

}  // namespace visitor