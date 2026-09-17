#pragma once

class Personality {
 public:
  Personality( float aggressiveness, float explorativeness, float boldness, float hoarder )
      : aggressiveness_( aggressiveness ), explorativeness_( explorativeness ), boldness_( boldness ), hoarder_( hoarder ) {}
  float aggressiveness_;
  float explorativeness_;
  float boldness_;
  float hoarder_;
};