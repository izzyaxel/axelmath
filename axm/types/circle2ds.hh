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

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator == (const circle& other) const -> bool
    {
      return this->radius == other.radius && this->position == other.position;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto move(const vec2<T>& offset) const -> circle
    {
      return {this->radius, this->position + offset};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto setPosition(const vec2<T>& pos) const -> circle
    {
      return {this->radius, pos};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getRadius() const -> T
    {
      return this->radius;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getDiameter() const -> T
    {
      return this->radius * (T)2;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getPosition() const -> vec2<T>
    {
      return this->position;
    }

  private:
    const T radius;
    const vec2<T> position;
  };
}
