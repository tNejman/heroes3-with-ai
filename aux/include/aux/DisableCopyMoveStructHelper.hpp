#pragma once

struct DisableCopyMove {  // NOLINT(cppcoreguidelines-special-member-functions)
  DisableCopyMove() = default;
  DisableCopyMove( const DisableCopyMove& ) = delete;
  DisableCopyMove( DisableCopyMove&& ) = delete;
  bool operator==( const DisableCopyMove& ) const noexcept = default;
};