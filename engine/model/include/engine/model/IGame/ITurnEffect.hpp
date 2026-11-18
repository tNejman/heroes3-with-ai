#pragma once

class ITurnEffect {  // NOLINT(cppcoreguidelines-special-member-functions)
 public:
  struct Duration {
    enum class Type : bool { N_TURNS, PERMANENT } type_;
    int n_duration_;
  };

  Duration duration_;  // NOLINT(misc-non-private-member-variables-in-classes)

 protected:
  virtual void doApply() const noexcept = 0;

 public:
  virtual ~ITurnEffect() = default;
  [[nodiscard]] ITurnEffect( Duration duration ) noexcept;

  void apply() noexcept {
  }
};