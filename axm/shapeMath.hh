#pragma once

#include "math.hh"
#include "types/aabb2ds.hh"
#include "types/circle2ds.hh"

namespace axm
{
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto isColliding(const circle<T>& a, const circle<T>& b) -> bool
  {
    const T distanceSquared = distSqr(a.getPosition(), b.getPosition());
    const T radiiSquared = std::pow(a.getRadius() + b.getRadius(), 2);
    return distanceSquared <= radiiSquared;
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto isColliding(const circle<T>& circle, const aabb2d<T>& aabb) -> bool
  {
    const vec2 circlePos = circle.getPosition();
    const vec2<T> closest
    {
      std::max(aabb.minX(), std::min(circlePos.x(), aabb.maxX())),
      std::max(aabb.minY(), std::min(circlePos.y(), aabb.maxY()))
    };
    const vec2<T> distance = circlePos - closest;
    const float distanceSquared = (distance.x() * distance.x()) + (distance.y() * distance.y());
    const float radiusSquared = circle.getRadius() * circle.getRadius();
    return distanceSquared <= radiusSquared;
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto isColliding(const aabb2d<T>& a, const aabb2d<T>& b) -> bool
  {
    if(a.maxX() < b.minX() || a.minX() > b.maxX())
    {
      return false;
    }

    if(a.maxY() < b.minY() || a.minY() > b.maxY())
    {
      return false;
    }

    return true;
  }
}
