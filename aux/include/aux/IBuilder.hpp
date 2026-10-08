#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstddef>
#include <memory>
#include <meta>

#include "aux/ConstexprCheck.hpp"

template <typename TypeBeingBuilt, typename Derived>
class IBuilder {
 private:
  template <typename T>
  using NoWrapper = T;

 private:  // NOLINT(readability-redundant-access-specifiers) // so the template above doesnt bind
  // consteval bool allMembersMatchTypeBeingBuiltAndAreOptionalWrappers() noexcept {
  //   auto const ctx{ std::meta::access_context::unchecked() };
  //   auto const derived_members{ std::meta::nonstatic_data_members_of( ^^Derived, ctx ) };
  //   auto const built_members{ std::meta::nonstatic_data_members_of( ^^TypeBeingBuilt, ctx ) };

  //   std::size_t built_index{ 0 };

  //   for ( std::meta::info const derived_member : derived_members ) {
  //     bool const derived_member_has_identifier{ std::meta::has_identifier( derived_member ) };
  //     CONSTEXPR_CHECK( derived_member_has_identifier );

  //     std::string_view const name{ std::meta::identifier_of( derived_member ) };
  //     while ( built_index < built_members.size()
  //             && ( !std::meta::has_identifier( built_members[built_index] )
  //                  || std::meta::identifier_of( built_members[built_index] ) != name ) ) {
  //       ++built_index;
  //     }

  //     bool const derived_member_exists_in_type_being_built_in_same_order{ built_index != built_members.size() };
  //     CONSTEXPR_CHECK( derived_member_exists_in_type_being_built_in_same_order );

  //     std::meta::info const type{ std::meta::dealias( std::meta::remove_cv( std::meta::type_of( derived_member ) ) )
  //     }; bool const derived_member_is_std_optional{ std::meta::has_template_arguments( type )
  //                                                && std::meta::template_of( type ) == ^^std::optional };
  //     CONSTEXPR_CHECK( derived_member_is_std_optional );

  //     bool const optional_value_type_matches_built_member_type{ std::meta::is_same_type(
  //         std::meta::template_arguments_of( type )[0], std::meta::type_of( built_members[built_index] ) ) };
  //     CONSTEXPR_CHECK( optional_value_type_matches_built_member_type );

  //     ++built_index;
  //   }

  //   return true;
  // }

  static consteval auto dataMembers() noexcept {
    constexpr auto CTX{ std::meta::access_context::unchecked() };
    constexpr std::size_t COUNT{ std::meta::nonstatic_data_members_of( ^^Derived, CTX ).size() };
    std::array<std::meta::info, COUNT> result{};
    std::ranges::copy( std::meta::nonstatic_data_members_of( ^^Derived, CTX ), result.begin() );
    return result;
  }

  template <typename Result, typename... Args>
  static Result make( Args&&... args ) {
    if constexpr ( std::same_as<Result, std::unique_ptr<TypeBeingBuilt>> ) {
      return std::make_unique<TypeBeingBuilt>( std::forward<Args>( args )... );
    } else if constexpr ( std::same_as<Result, std::shared_ptr<TypeBeingBuilt>> ) {
      return std::make_shared<TypeBeingBuilt>( std::forward<Args>( args )... );
    } else {
      static_assert( std::same_as<Result, TypeBeingBuilt>, "Unsupported wrapper" );
      return TypeBeingBuilt{ std::forward<Args>( args )... };
    }
  }

  friend class CleanerGuard;
  class CleanerGuard {  // NOLINT(cppcoreguidelines-special-member-functions)
   private:
    IBuilder& builder_to_clean_;  // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)

   public:
    CleanerGuard( IBuilder& builder_to_clean ) noexcept : builder_to_clean_( builder_to_clean ) {
    }
    ~CleanerGuard() noexcept {
      builder_to_clean_.reset();
    }
  };

 protected:
  virtual void generateDefaultsForUnsetParams() noexcept = 0;
  virtual int generateId() noexcept = 0;

  void reset() noexcept {
    constexpr auto CTX{ std::meta::access_context::unchecked() };
    auto& self{ static_cast<Derived&>( *this ) };
    template for ( constexpr auto m :
                   std::define_static_array( std::meta::nonstatic_data_members_of( ^^Derived, CTX ) ) ) {
      self.[:m:] = std::nullopt;
    }
  }

 public:
  // constexpr IBuilder() noexcept {
  // static_assert( this->allMembersMatchTypeBeingBuiltAndAreOptionalWrappers(),
  //                "every non-static data member of Derived must be std::optional<T> and match TypeBeingBuilt in type "
  //                "underneath <T> and name" );
  // }
  constexpr IBuilder() = default;
  virtual ~IBuilder() = default;
  IBuilder( const IBuilder& ) = delete;
  IBuilder( IBuilder&& ) = delete;
  IBuilder& operator=( const IBuilder& ) = delete;
  IBuilder& operator=( IBuilder&& ) = delete;

  template <template <typename> typename Wrapper = NoWrapper>
  Wrapper<TypeBeingBuilt> build() noexcept {
    const CleanerGuard cleaner_guard{ *this };

    static constexpr auto [... members] = dataMembers();
    auto& self{ static_cast<Derived&>( *this ) };
    generateDefaultsForUnsetParams();
    return make<Wrapper<TypeBeingBuilt>>( generateId(), std::move( *self.[:members:] )... );
  }
};