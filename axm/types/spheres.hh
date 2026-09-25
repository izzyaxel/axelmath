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

    Const UseResult CannotFail
    auto operator == (const sphere& other) const -> bool
    {
      return this->radius == other.radius && this->position == other.position;
    }

    Const UseResult CannotFail
    auto move(const vec3<T>& offset) const -> sphere
    {
      return {this->radius, this->position + offset};
    }

    Const UseResult CannotFail
    auto setPosition(const vec3<T>& pos) const -> sphere
    {
      return {this->radius, pos};
    }

    Const UseResult CannotFail
    auto getRadius() const -> T
    {
      return this->radius;
    }

    Const UseResult CannotFail
    auto getDiameter() const -> T
    {
      return this->radius * T(2);
    }

    Const UseResult CannotFail
    auto getPosition() const -> vec3<T>
    {
      return this->position;
    }

  private:
    T radius{};
    vec3<T> position{};
  };
}
