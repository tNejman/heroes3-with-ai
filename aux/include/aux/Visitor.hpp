#pragma once

template <typename T>
class VisitorFor {  // NOLINT(cppcoreguidelines-special-member-functions)
  virtual ~VisitorFor() = default;
  virtual void visit( const T& node ) noexcept = 0;
};

template <typename Derived, typename Base, typename... Ts>
class VisitorImpl;

template <typename... Ts>
class Visitor : VisitorFor<Ts>... {
  using VisitorFor<Ts>::visit...;

  template <typename Derived>
  using Impl = VisitorImpl<Derived, Visitor, Ts...>;
};

template <typename Derived, typename Base>
class VisitorImpl<Derived, Base> : Base {
  using Base::visit;
};

template <typename Derived, typename Base, typename T, typename... Ts>
class VisitorImpl<Derived, Base, T, Ts...> : VisitorImpl<Derived, Base, Ts...> {
  using VisitorImpl<Derived, Base, Ts...>::visit;

  void visit( const T& node ) noexcept override {
    static_cast<const Derived&>( *this ).visitNode( node );
  }
};

template <typename Derived, typename Base, typename VisitorT>
class Visitable : Base {
  void accept( VisitorT& visitor ) override {
    visitor.visit( static_cast<Derived&>( *this ) );
  }
};