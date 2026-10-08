#pragma once

#include <concepts>
#include <cstddef>
#include <limits>
#include <memory>
#include <meta>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

template <typename T>
class Builder;

template <typename T>
struct BuilderDefaults {
  using NotSpecialized = void;
};

template <typename T>
struct BuilderIdGenerator {
  using NotSpecialized = void;
};

namespace detail {

consteval auto constructorsOf( std::meta::info type ) -> std::vector<std::meta::info> {
  std::vector<std::meta::info> result;
  for ( std::meta::info member : std::meta::members_of( type, std::meta::access_context::current() ) ) {
    if ( std::meta::is_constructor( member ) && !std::meta::is_default_constructor( member )
         && !std::meta::is_copy_constructor( member ) && !std::meta::is_move_constructor( member ) ) {
      result.push_back( member );
    }
  }
  return result;
}

consteval auto constructorOf( std::meta::info type ) -> std::meta::info {
  return constructorsOf( type ).front();
}

consteval auto setterName( std::string_view field_name ) -> std::string {
  std::string result{ "set" };
  bool capitalize_next = true;
  for ( char c : field_name ) {
    if ( c == '_' ) {
      capitalize_next = true;
      continue;
    }
    result += ( capitalize_next && c >= 'a' && c <= 'z' ) ? static_cast<char>( c - 'a' + 'A' ) : c;
    capitalize_next = false;
  }
  return result;
}

consteval auto isIdParameter( std::meta::info parameter ) -> bool {
  return std::meta::has_identifier( parameter ) && std::meta::identifier_of( parameter ) == "id";
}

consteval auto fieldParametersOf( std::meta::info type ) -> std::vector<std::meta::info> {
  std::vector<std::meta::info> result;
  for ( std::meta::info parameter : std::meta::parameters_of( constructorOf( type ) ) ) {
    if ( !isIdParameter( parameter ) ) {
      result.push_back( parameter );
    }
  }
  return result;
}

inline constexpr std::size_t no_id_index = std::numeric_limits<std::size_t>::max();

consteval auto idIndexOf( std::meta::info type ) -> std::size_t {
  std::vector<std::meta::info> parameters{ std::meta::parameters_of( constructorOf( type ) ) };
  for ( std::size_t i = 0; i < parameters.size(); ++i ) {
    if ( isIdParameter( parameters[i] ) ) {
      return i;
    }
  }
  return no_id_index;
}

consteval auto toDecimal( std::size_t value ) -> std::string {
  std::string digits;
  do {
    digits.insert( digits.begin(), static_cast<char>( '0' + static_cast<int>( value % 10 ) ) );
    value /= 10;
  } while ( value != 0 );
  return digits;
}

consteval auto displayType( std::meta::info type ) -> std::string {
  return std::string{ std::meta::display_string_of( type ) };
}

consteval auto defaultOf( std::meta::info defaults, std::string_view field_name ) -> std::meta::info {
  for ( std::meta::info member : std::meta::members_of( defaults, std::meta::access_context::unchecked() ) ) {
    if ( std::meta::is_variable( member ) && std::meta::has_identifier( member )
         && std::meta::identifier_of( member ) == field_name ) {
      return member;
    }
  }
  return std::meta::info{};
}

consteval auto defaultsFor( std::meta::info defaults, std::span<const std::meta::info> fields )
    -> std::vector<std::meta::info> {
  std::vector<std::meta::info> result;
  for ( std::meta::info field : fields ) {
    result.push_back( defaultOf( defaults, std::meta::identifier_of( field ) ) );
  }
  return result;
}

consteval auto defaultsDiagnostic( std::meta::info type, std::meta::info defaults, bool specialized ) -> std::string {
  if ( constructorsOf( type ).size() != 1 ) {
    return {};
  }

  std::vector<std::meta::info> parameters{ fieldParametersOf( type ) };
  std::string type_name{ displayType( type ) };
  std::string defaults_name{ displayType( defaults ) };

  if ( !specialized ) {
    std::string message{ "no defaults provided for Builder<" + type_name
                         + ">. Add this specialization and fill in the values:\n\ntemplate <>\nstruct " + defaults_name
                         + " {\n" };
    for ( std::meta::info parameter : parameters ) {
      std::string_view field_name = std::meta::has_identifier( parameter ) ? std::meta::identifier_of( parameter )
                                                                           : std::string_view{ "<unnamed>" };
      message += "    static inline const " + displayType( std::meta::remove_cvref( std::meta::type_of( parameter ) ) )
                 + " " + field_name + "{...};\n";
    }
    message += "};";
    return message;
  }

  std::string message;
  for ( std::size_t i = 0; i < parameters.size(); ++i ) {
    if ( !std::meta::has_identifier( parameters[i] ) ) {
      message += "\n  - constructor parameter #" + toDecimal( i ) + " of " + type_name
                 + " has no name, so it cannot be matched to a default";
      continue;
    }
    std::string_view field_name = std::meta::identifier_of( parameters[i] );
    std::meta::info field_type = std::meta::remove_cvref( std::meta::type_of( parameters[i] ) );
    std::meta::info default_member = defaultOf( defaults, field_name );
    if ( default_member == std::meta::info{} ) {
      message +=
          "\n  - missing default for constructor parameter '" + displayType( field_type ) + " " + field_name + "'";
    } else if ( !std::meta::is_same_type( std::meta::remove_cv( std::meta::type_of( default_member ) ), field_type ) ) {
      message += "\n  - " + defaults_name + "::" + field_name + " has type '"
                 + displayType( std::meta::type_of( default_member ) ) + "', but constructor parameter '" + field_name
                 + "' has type '" + displayType( field_type ) + "'";
    }
  }
  for ( std::meta::info member : std::meta::members_of( defaults, std::meta::access_context::unchecked() ) ) {
    if ( !std::meta::is_variable( member ) || !std::meta::has_identifier( member ) ) {
      continue;
    }
    if ( std::meta::identifier_of( member ) == "id" && idIndexOf( type ) != no_id_index ) {
      message += "\n  - " + defaults_name + "::id must be removed: id is taken from BuilderIdGenerator<" + type_name
                 + "> on every build()";
      continue;
    }
    bool matched = false;
    for ( std::meta::info parameter : parameters ) {
      if ( std::meta::has_identifier( parameter )
           && std::meta::identifier_of( parameter ) == std::meta::identifier_of( member ) ) {
        matched = true;
        break;
      }
    }
    if ( !matched ) {
      message += "\n  - " + defaults_name + "::" + std::meta::identifier_of( member )
                 + " does not match any constructor parameter of " + type_name;
    }
  }
  if ( message.empty() ) {
    return message;
  }
  return defaults_name + " does not match the constructor of " + type_name + ":" + message;
}

consteval auto idGeneratorDiagnostic( std::meta::info type, std::meta::info generator_trait, bool specialized )
    -> std::string {
  if ( constructorsOf( type ).size() != 1 ) {
    return {};
  }
  std::size_t id_position = idIndexOf( type );
  if ( id_position == no_id_index ) {
    return {};
  }

  std::string type_name{ displayType( type ) };
  std::string trait_name{ displayType( generator_trait ) };
  std::meta::info id_type =
      std::meta::remove_cvref( std::meta::type_of( std::meta::parameters_of( constructorOf( type ) )[id_position] ) );
  if ( !std::meta::is_same_type( id_type, ^^int ) ) {
    return "constructor parameter 'id' of " + type_name + " has type '" + displayType( id_type )
           + "', but generated ids are 'int'";
  }

  if ( !specialized ) {
    return type_name + " has an 'id' constructor parameter, so Builder<" + type_name
           + "> needs an id generator. Add this specialization and fill in the body:\n\ntemplate <>\nstruct "
           + trait_name + " {\n    static inline auto generator = []() -> int { ... };\n};";
  }

  for ( std::meta::info member : std::meta::members_of( generator_trait, std::meta::access_context::unchecked() ) ) {
    if ( !std::meta::has_identifier( member ) || std::meta::identifier_of( member ) != "generator" ) {
      continue;
    }
    if ( !std::meta::is_static_member( member ) ) {
      return trait_name + "::generator must be static";
    }
    std::meta::info callable_type = std::meta::is_function( member )
                                        ? std::meta::type_of( member )
                                        : std::meta::add_lvalue_reference( std::meta::type_of( member ) );
    if ( !std::meta::is_invocable_type( callable_type, std::vector<std::meta::info>{} ) ) {
      return trait_name + "::generator is not callable with no arguments";
    }
    std::meta::info result_type = std::meta::invoke_result( callable_type, std::vector<std::meta::info>{} );
    if ( !std::meta::is_same_type( result_type, ^^int ) ) {
      return trait_name + "::generator returns '" + displayType( result_type ) + "', but must return 'int'";
    }
    return {};
  }
  return trait_name + " has no static member 'generator' (a callable taking no arguments and returning int)";
}

consteval auto namedMemberSpec( std::meta::info type, std::string_view name ) -> std::meta::info {
  return std::meta::data_member_spec(
      type, { .name = name, .alignment = std::nullopt, .bit_width = std::nullopt, .no_unique_address = false } );
}

template <typename Owner, std::size_t field_index>
class Setter {
 public:
  Setter() = default;
  Setter( const Setter& ) noexcept {
  }
  auto operator=( const Setter& ) noexcept -> Setter& {
    return *this;
  }

  template <typename Value>
  auto operator()( Value&& value ) const -> Owner&& {
    constexpr std::meta::info member = Owner::value_members[field_index];
    owner_->[:member:] = std::forward<Value>( value );
    return std::move( *owner_ );
  }

 private:
  friend Owner;
  Owner* owner_ = nullptr;
};

template <typename T>
struct BuilderFields {
  static_assert( constructorsOf( ^^T ).size() == 1,
                 "T must have exactly one public constructor other than default/copy/move" );

  static constexpr bool has_defaults = !requires { typename BuilderDefaults<T>::NotSpecialized; };
  static constexpr std::string_view diagnostic =
      std::define_static_string( defaultsDiagnostic( ^^T, ^^BuilderDefaults<T>, has_defaults ) );
  static_assert( diagnostic.empty(), diagnostic );

  static constexpr bool has_id_generator = !requires { typename BuilderIdGenerator<T>::NotSpecialized; };
  static constexpr std::string_view id_diagnostic =
      std::define_static_string( idGeneratorDiagnostic( ^^T, ^^BuilderIdGenerator<T>, has_id_generator ) );
  static_assert( id_diagnostic.empty(), id_diagnostic );

  struct Type;

  consteval {
    std::vector<std::meta::info> parameters = fieldParametersOf( ^^T );
    std::vector<std::meta::info> specs;
    for ( std::meta::info parameter : parameters ) {
      specs.push_back( namedMemberSpec( std::meta::remove_cvref( std::meta::type_of( parameter ) ),
                                        std::meta::identifier_of( parameter ) ) );
    }
    for ( std::size_t i = 0; i < parameters.size(); ++i ) {
      specs.push_back( namedMemberSpec( std::meta::substitute( ^^Setter,
                                                               {
                                                                   ^^Builder<T>, std::meta::reflect_constant( i ) } ),
                                        setterName( std::meta::identifier_of( parameters[i] ) ) ) );
    }
    std::meta::define_aggregate( ^^Type, specs );
  }
};

}  // namespace detail

template <typename T>
class Builder : public detail::BuilderFields<T>::Type {
  using Fields = typename detail::BuilderFields<T>::Type;

  template <typename, std::size_t>
  friend class detail::Setter;

  static constexpr std::size_t field_count = detail::fieldParametersOf( ^^T ).size();
  static constexpr std::size_t parameter_count = std::meta::parameters_of( detail::constructorOf( ^^T ) ).size();
  static constexpr std::size_t id_index = detail::idIndexOf( ^^T );
  static constexpr std::span<const std::meta::info> all_members = std::define_static_array(
      std::meta::nonstatic_data_members_of( ^^Fields, std::meta::access_context::unchecked() ) );
  static constexpr std::span<const std::meta::info> value_members = all_members.first( field_count );
  static constexpr std::span<const std::meta::info> setter_members = all_members.subspan( field_count );
  static constexpr std::span<const std::meta::info> default_members =
      std::define_static_array( detail::defaultsFor( ^^BuilderDefaults<T>, value_members ) );
  static constexpr auto default_pointers = []<std::size_t... indices>( std::index_sequence<indices...> ) {
    return std::tuple{ &[:default_members[indices]:]... };
  }( std::make_index_sequence<field_count>{} );

 public:
  Builder() : Fields{ makeDefaultFields() } {
    bindSetters();
  }
  Builder( const Builder& other ) : Fields{ other } {
    bindSetters();
  }
  Builder( Builder&& other ) : Fields{ std::move( other ) } {
    bindSetters();
  }
  auto operator=( const Builder& ) -> Builder& = default;
  auto operator=( Builder&& ) -> Builder& = default;

  template <template <typename...> class Wrapper = std::type_identity_t>
  auto build() -> Wrapper<T> {
    using Result = Wrapper<T>;
    Result result = [this]<std::size_t... indices>( std::index_sequence<indices...> ) -> Result {
      if constexpr ( std::same_as<Result, std::unique_ptr<T>> ) {
        return std::make_unique<T>( this->template argument<indices>()... );
      } else if constexpr ( std::same_as<Result, std::shared_ptr<T>> ) {
        return std::make_shared<T>( this->template argument<indices>()... );
      } else {
        static_assert( std::same_as<Result, T>, "Unsupported wrapper" );
        return T{ this->template argument<indices>()... };
      }
    }( std::make_index_sequence<parameter_count>{} );
    reset();
    return result;
  }

 private:
  void bindSetters() {
    template for ( constexpr std::meta::info member : setter_members ) {
      this->[:member:].owner_ = this;
    }
  }

  template <std::size_t parameter_index>
  auto argument() -> decltype( auto ) {
    if constexpr ( parameter_index == id_index ) {
      return BuilderIdGenerator<T>::generator();
    } else {
      constexpr std::size_t field_index = parameter_index > id_index ? parameter_index - 1 : parameter_index;
      return std::move( this->[:value_members[field_index]:] );
    }
  }

  static auto makeDefaultFields() -> Fields {
    return []<std::size_t... indices>( std::index_sequence<indices...> ) -> Fields {
      return Fields{ *std::get<indices>( default_pointers )..., detail::Setter<Builder, indices>{}... };
    }( std::make_index_sequence<field_count>{} );
  }

  void reset() {
    [this]<std::size_t... indices>( std::index_sequence<indices...> ) {
      ( ( this->[:value_members[indices]:] = *std::get<indices>( default_pointers ) ), ... );
    }( std::make_index_sequence<field_count>{} );
  }
};