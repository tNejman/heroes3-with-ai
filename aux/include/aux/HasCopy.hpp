#pragma once

template <typename T>
concept HasCopy = requires {
  static_cast<T (T::*)() const noexcept>(&T::copy);
};