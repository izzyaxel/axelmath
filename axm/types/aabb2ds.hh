#pragma once

#include "../aliases.hh"
#include "../concepts.hh"
#include "../math.hh"

#include "vec2s.hh"

namespace axm
{

  template <IsNumeric T>
  struct aabb2d
  {
    aabb2d() = default;

    aabb2d(const vec2<T>& upperLeft, const vec2<T>& lowerRight)
    {
      this->upperLeft = upperLeft;
      this->lowerRight = lowerRight;
      vec2<T> distance = lowerRight - upperLeft;
      this->center = lowerRight - distance / (T)2;
    }

    aabb2d(const vec2<T>& center, const T width, const T height)
    {
      this->center = center;
      float halfWidth = (float)width / (T)2;
      float halfHeight = (float)height / (T)2;

      this->upperLeft.x() = this->center.x() - halfWidth;
      this->lowerRight.x() = this->center.x() + halfWidth;

      this->upperLeft.y() = this->center.y() + halfHeight;
      this->lowerRight.y() = this->center.y() - halfHeight;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto move(const T xOffset, const T yOffset) const -> aabb2d
    {
      vec2 off{xOffset, yOffset};
      return {this->upperLeft + off, this->lowerRight + off};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto move(const vec2<T> offset) const -> aabb2d
    {
      return {this->upperLeft + offset, this->lowerRight + offset};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto setPosition(const vec2<T> cent) const -> aabb2d
    {
      T width = this->getWidth();
      T height = this->getHeight();
      return {cent, width, height};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto minX() const -> T
    {
      return this->upperLeft.x();
    }

    CONST USE_RESULT CANNOT_FAIL
    auto maxX() const -> T
    {
      return this->lowerRight.x();
    }

    CONST USE_RESULT CANNOT_FAIL
    auto minY() const -> T
    {
      return this->upperLeft.y();
    }

    CONST USE_RESULT CANNOT_FAIL
    auto maxY() const -> T
    {
      return this->lowerRight.x();
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getCenter() const -> vec2<T>
    {
      return this->center;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getUpperLeft() const -> vec2<T>
    {
      return this->upperLeft;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getUpperRight() const -> vec2<T>
    {
      return vec2{this->lowerRight.x(), this->upperLeft.y()};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getLowerLeft() const -> vec2<T>
    {
      return this->lowerRight;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getLowerRight() const -> vec2<T>
    {
      return vec2{this->upperLeft.x(), this->lowerRight.y};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getWidth() const -> T
    {
      return dist(this->upperLeft.x(), this->lowerRight.x());
    }

    CONST USE_RESULT CANNOT_FAIL
    auto getHeight() const -> T
    {
      return dist(this->upperLeft.y(), this->lowerRight.y());
    }

  private:
    vec2<T> center{};
    vec2<T> upperLeft{};
    vec2<T> lowerRight{};
  };
}
