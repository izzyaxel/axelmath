#pragma once

#include "../aliases.hh"
#include "../concepts.hh"

#include "vec2s.hh"

namespace axm
{

  template <IsNumeric T>
  struct circle
  {
    circle() = default;

    circle(const T radius, const vec2<T>& position)
    {
      this->radius = radius;
      this->position = position;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator == (const circle& other) const -> bool
    {
      return this->radius == other.radius && this->position == other.position;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto move(const vec2<T>& offset) -> circle
    {
      return {this->radius, this->position + offset};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto setPosition(const vec2<T>& pos) -> circle
    {
      return {this->radius, pos};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getRadius() -> T
    {
      return this->radius;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getDiameter() -> T
    {
      return this->radius * (T)2;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getPosition() -> vec2<T>
    {
      return this->position;
    }

  private:
    T radius = 0;
    vec2<T> position{0};
  };
}
