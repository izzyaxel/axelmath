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

  CONST USE_RESULT CANNOT_FAIL
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
  CONST USE_RESULT CANNOT_FAIL
  auto degToRad(T degree) -> T
  {
    return degree * (std::numbers::pi / (T)180);
  }

  template <IsNumeric T>
  CONST USE_RESULT CANNOT_FAIL
  auto dist(T a, T b) -> T
  {
    return std::abs(a - b);
  }

  template <IsNumeric T>
  CONST USE_RESULT CANNOT_FAIL
  auto dist(vec2<T>& a, vec2<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x - a.x, 2) + std::powf(b.y - a.y, 2));
  }

  template <IsNumeric T>
  CONST USE_RESULT CANNOT_FAIL
  auto distSqr(vec2<T>& a, vec2<T>& b) -> T
  {
    return std::powf(b.x - a.x, 2) + std::powf(b.y - a.y, 2);
  }

  template <IsNumeric T>
  CONST USE_RESULT CANNOT_FAIL
  auto dist(vec3<T>& a, vec3<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x - a.x, 2) + std::powf(b.y - a.y, 2) + std::powf(b.z - a.z, 2));
  }

  template <IsNumeric T>
  CONST USE_RESULT CANNOT_FAIL
  auto distSqr(vec3<T>& a, vec3<T>& b) -> T
  {
    return std::powf(b.x - a.x, 2) + std::powf(b.y - a.y, 2) + std::powf(b.z - a.z, 2);
  }
}
