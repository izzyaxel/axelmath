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

    Const UseResult CannotFail
    auto operator == (const circle& other) const -> bool
    {
      return this->radius == other.radius && this->position == other.position;
    }

    Const UseResult CannotFail
    auto move(const vec2<T>& offset) const -> circle
    {
      return {this->radius, this->position + offset};
    }

    Const UseResult CannotFail
    auto setPosition(const vec2<T>& pos) const -> circle
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
    auto getPosition() const -> vec2<T>
    {
      return this->position;
    }

  private:
    T radius;
    vec2<T> position;
  };
}
