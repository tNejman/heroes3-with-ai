#pragma once

#include <variant>

template <typename T, typename V>
inline constexpr bool IS_VARIANT_MEMBER_V = false;

template <typename T, typename... Ts>
inline constexpr bool IS_VARIANT_MEMBER_V<T, std::variant<Ts...>> = ( std::is_same_v<T, Ts> || ... );

template <typename T, typename V>
concept VariantMember = IS_VARIANT_MEMBER_V<T, V>;