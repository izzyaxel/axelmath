#pragma once

#include <cstdint>
#include <limits>

namespace axm
{
  /// Tag for functions that can return something indicating an error state occurred
  /// A non-enforceable contract with the user of this library
#define CAN_FAIL

  /// Tag for functions that have no possible error state
  /// A non-enforceable contract with the user of this library
#define CANNOT_FAIL

  /// Tag for functions whose return values should be stored and/or used
  /// On GCC/MinGW this is an enforced contract with the user of this library
  /// On most other compilers this is a non-enforceable contract with the user of this library
#define USE_RESULT [[nodiscard]]

  /// Tag for functions that do not mutate the state of their parent class or anything passed into them, and cannot read non-volatile global variables
  /// On GCC/MinGW this is an enforced contract with the user of this library
  /// On most other compilers this is a non-enforceable contract with the user of this library
#define GNUPURE [[gnu::pure]]

  /// Tag for functions that depend only on the arguments passed to them
  /// On GCC/MinGW this is an enforced contract with the user of this library
  /// On most other compilers this is a non-enforceable contract with the user of this library
#define GNUCONST [[gnu::const]]

  using i8 = int8_t;
  using u8 = uint8_t;
  using i16 = int16_t;
  using u16 = uint16_t;
  using i32 = int32_t;
  using u32 = uint32_t;

  constexpr inline float EPSILON = std::numeric_limits<float>::epsilon();
}
