#pragma once

struct DisableCopyMove {  // NOLINT(cppcoreguidelines-special-member-functions)
  [[nodiscard]] constexpr DisableCopyMove() noexcept = default;
  DisableCopyMove( const DisableCopyMove& ) = delete;
  DisableCopyMove( DisableCopyMove&& ) = delete;
  [[nodiscard]] constexpr bool operator==( const DisableCopyMove& ) const noexcept = default;
};