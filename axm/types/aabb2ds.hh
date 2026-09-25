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

    aabb2d(const T minX, const T maxX, const T minY, const T maxY)
    {
      this->lowerRight = {minX, minY};
      this->upperLeft = {maxX, maxY};
    }

    aabb2d(const vec2<T>& upperLeft, const vec2<T>& lowerRight)
    {
      this->upperLeft = upperLeft;
      this->lowerRight = lowerRight;
      vec2<T> distance = lowerRight - upperLeft;
      this->center = lowerRight - distance / T(2);
    }

    aabb2d(const vec2<T>& center, const T width, const T height)
    {
      this->center = center;
      T halfW = width / T(2);
      T halfH = height / T(2);

      this->upperLeft = {center.x() - halfW, center.y() + halfH};
      this->lowerRight = {center.x() + halfW, center.y() - halfH};
    }

    Const UseResult CannotFail
    auto move(const T xOffset, const T yOffset) const -> aabb2d
    {
      vec2 off{xOffset, yOffset};
      return {this->upperLeft + off, this->lowerRight + off};
    }

    Const UseResult CannotFail
    auto move(const vec2<T> offset) const -> aabb2d
    {
      return {this->upperLeft + offset, this->lowerRight + offset};
    }

    Const UseResult CannotFail
    auto setPosition(const vec2<T> cent) const -> aabb2d
    {
      T width = this->getWidth();
      T height = this->getHeight();
      return {cent, width, height};
    }

    Const UseResult CannotFail
    auto minX() const -> T
    {
      return this->upperLeft.x();
    }

    Const UseResult CannotFail
    auto maxX() const -> T
    {
      return this->lowerRight.x();
    }

    Const UseResult CannotFail
    auto minY() const -> T
    {
      return this->lowerRight.y();
    }

    Const UseResult CannotFail
    auto maxY() const -> T
    {
      return this->upperLeft.y();
    }

    Const UseResult CannotFail
    auto getCenter() const -> vec2<T>
    {
      return this->center;
    }

    Const UseResult CannotFail
    auto getUpperLeft() const -> vec2<T>
    {
      return this->upperLeft;
    }

    Const UseResult CannotFail
    auto getUpperRight() const -> vec2<T>
    {
      return vec2{this->lowerRight.x(), this->upperLeft.y()};
    }

    Const UseResult CannotFail
    auto getLowerLeft() const -> vec2<T>
    {
      return vec2{this->upperLeft.x(), this->lowerRight.y()};
    }

    Const UseResult CannotFail
    auto getLowerRight() const -> vec2<T>
    {
      return this->lowerRight;
    }

    Const UseResult CannotFail
    auto getWidth() const -> T
    {
      return dist(this->upperLeft.x(), this->lowerRight.x());
    }

    Const UseResult CannotFail
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
