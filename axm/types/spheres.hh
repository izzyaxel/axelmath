#pragma once

#include "../concepts.hh"

#include "vec3s.hh"

namespace axm
{
  template <IsNumeric T>
  struct sphere
  {
    sphere() = default;

    sphere(const T radius, const vec3<T>& position)
    {
      this->radius = radius;
      this->position = position;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator == (const sphere& other) const -> bool
    {
      return this->radius == other.radius && this->position == other.position;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto move(const vec3<T>& offset) const -> sphere
    {
      return {this->radius, this->position + offset};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto setPosition(const vec3<T>& pos) const -> sphere
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
    auto getPosition() const -> vec3<T>
    {
      return this->position;
    }

  private:
    T radius{};
    vec3<T> position{};
  };
}
