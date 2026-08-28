#pragma once

#include "aliases.hh"
#include "concepts.hh"

#include <numbers>
#include <algorithm>
#include <cmath>

namespace axm
{
  template <typename T>
  struct vec2;

  template <typename T>
  struct vec3;

  GNUCONST USE_RESULT CANNOT_FAIL
  inline auto closeEnough(const float val, const float target) -> bool
  {
    if(std::abs(val - target) <= 1e-6)
    {
      return true;
    }
    const float max = std::max(std::abs(val), std::abs(target));
    return std::abs(val - target) <= max * 1e-8f;
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto degToRad(const T degree) -> T
  {
    return degree * (std::numbers::pi / (T)180);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const T a, const T b) -> T
  {
    return std::abs(a - b);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const vec2<T>& a, const vec2<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2));
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto distSqr(const vec2<T>& a, const vec2<T>& b) -> T
  {
    return std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const vec3<T>& a, const vec3<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2) + std::powf(b.z() - a.z(), (T)2));
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto distSqr(const vec3<T>& a, const vec3<T>& b) -> T
  {
    return std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2) + std::powf(b.z() - a.z(), (T)2);
  }
}
