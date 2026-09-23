#pragma once

#include <type_traits>

template <typename T>
concept Enum = std::is_enum_v<T>;