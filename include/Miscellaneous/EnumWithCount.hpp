#pragma once

#include <type_traits>

template <typename T>
concept Enum = std::is_enum_v<T>;

template <typename T>
concept EnumWithCount = std::is_enum_v<T> && requires { T::COUNT; };

template <typename T>
concept EnumWithCountOrNone = std::is_enum_v<T> && ( requires { T::COUNT; } || requires { T::NONE; } );