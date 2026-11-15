#pragma once

class Personality {
 public:
  [[nodiscard]] constexpr Personality( float aggressiveness, float explorativeness, float boldness,
                                       float hoarder ) noexcept
      : aggressiveness_( aggressiveness ),
        explorativeness_( explorativeness ),
        boldness_( boldness ),
        hoarder_( hoarder ) {
  }
  float aggressiveness_;
  float explorativeness_;
  float boldness_;
  float hoarder_;
};