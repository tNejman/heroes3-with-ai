#pragma once

#include <aux/Range.hpp>

#include "SFML/Graphics/Rect.hpp"

class ISlider {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
 private:
  sf::IntRect loc_size_;

 public:
  virtual ~ISlider() = default;
  [[nodiscard]] constexpr ISlider( sf::IntRect loc_size ) noexcept;
  [[nodiscard]] constexpr sf::IntRect getLocSizeRect() const noexcept;
};

/* ==== @CONSTEXPR IMPL ==== */

[[nodiscard]] constexpr ISlider::ISlider( sf::IntRect loc_size ) noexcept : loc_size_( loc_size ) {
}

[[nodiscard]] constexpr sf::IntRect ISlider::getLocSizeRect() const noexcept {
  return loc_size_;
}

/* ==== @DERIVED ==== */

template <typename RangeT, typename StepT>
class SliderOf : public ISlider {
 private:
  Range<RangeT, StepT> range_;

 public:
  [[nodiscard]] constexpr SliderOf( Range<RangeT, StepT> range, sf::IntRect size ) noexcept;
  [[nodiscard]] constexpr Range<RangeT, StepT> getRange() const noexcept;
};

/* ==== @CONSTEXPR IMPL ==== */

template <typename RangeT, typename StepT>
[[nodiscard]] constexpr SliderOf<RangeT, StepT>::SliderOf( Range<RangeT, StepT> range, sf::IntRect size ) noexcept
    : ISlider( size ), range_( range ) {
}

template <typename RangeT, typename StepT>
[[nodiscard]] constexpr Range<RangeT, StepT> SliderOf<RangeT, StepT>::getRange() const noexcept {
  return range_;
}

/* ==== @DERIVED 2ND DEG ==== */

class IntSlider : public SliderOf<int, int> {};