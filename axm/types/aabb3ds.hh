#pragma once

#include "../concepts.hh"
#include "vec3s.hh"

namespace axm
{

  /// A 3-dimensional axis-aligned bounding box
  /// Z is forward/back
  template <IsNumeric T>
  struct aabb3d
  {
    aabb3d() = default;

    aabb3d(const T minX, const T maxX, const T minY, const T maxY, const T minZ, const T maxZ)
    {
      this->botLL = {minX, minY, minZ};
      this->topUR = {maxX, maxY, maxZ};
    }

    /// Define an aabb3d by its extents
    /// @param topUR With the center of the aabb as 0, 0, 0, all 3 axes are positive
    /// @param botLL With the center of the aabb as 0, 0, 0, all 3 axes are negative
    aabb3d(const vec3<T>& topUR, const vec3<T>& botLL)
    {
      this->topUR = topUR;
      this->botLL = botLL;

      vec3 offset
      {
        (std::max(botLL.x(), topUR.x()) - std::min(botLL.x(), topUR.x())) / (T)2,
        (std::max(botLL.y(), topUR.y()) - std::min(botLL.y(), topUR.y())) / (T)2,
        (std::max(botLL.z(), topUR.z()) - std::min(botLL.z(), topUR.z())) / (T)2
      };
    }

    /// Define an aabb3d by its center point and dimensions
    /// @param center The center of the aabb
    /// @param dimensions The dimensions of the aabb, evenly distributed around the center
    aabb3d(const vec3<T>& center, const vec3<T> dimensions)
    {
      vec3 half{dimensions.width() / (T)2, dimensions.height() / (T)2, dimensions.depth() / (T)2};
      this->botLL = center + half;
      this->topUR = center - half;
    }

    CANNOT_FAIL
    auto move(const vec3<T>& amount) -> void
    {
      this->topUR += amount;
      this->botLL += amount;
    }

    CANNOT_FAIL
    auto setPosition(const vec3<T>& newCenterPosition) -> void
    {
      vec3 offset = this->halfExtents();
      this->topUR = newCenterPosition + offset;
      this->botLL = newCenterPosition - offset;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto extents() const -> vec3<T>
    {
      return
      {
        std::max(botLL.x(), topUR.x()) - std::min(botLL.x(), topUR.x()),
        std::max(botLL.y(), topUR.y()) - std::min(botLL.y(), topUR.y()),
        std::max(botLL.z(), topUR.z()) - std::min(botLL.z(), topUR.z())
      };
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto halfExtents() const -> vec3<T>
    {
      return this->extents() / (T)2;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getCenter() const -> vec3<T>
    {
      vec3 offset = halfExtents();
      return this->botLL + halfExtents();
    }

    //Corner getters
    GNUCONST USE_RESULT CANNOT_FAIL
    auto getTopUL() const -> vec3<T>
    {
      return vec2{this->botLL.x(), this->topUR.y(), this->topUR.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getTopUR() const -> vec3<T>
    {
      return this->topUR;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getTopLR() const -> vec3<T>
    {
      return vec2{this->topUR.x(), this->topUR.y(), this->botLL.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getTopLL() const -> vec3<T>
    {
      return vec2{this->botLL.x(), this->topUR.y(), this->botLL.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getBotUL() const -> vec3<T>
    {
      return vec2{this->botLL.x(), this->botLL.y(), this->topUR.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getBotUR() const -> vec3<T>
    {
      return vec2{this->topUR.x(), this->botLL.y(), this->topUR.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getBotLR() const -> vec3<T>
    {
      return vec2{this->topUR.x(), this->botLL.y(), this->botLL.z()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getBotLL() const -> vec3<T>
    {
      return this->botLL;
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getWidth() const -> T
    {
      return dist(this->topUR.x(), this->botLL.x());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getHeight() const -> T
    {
      return dist(this->topUR.y(), this->botLL.y());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto getDepth() const -> T
    {
      return dist(this->topUR.z(), this->botLL.z());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto minX() const -> T
    {
      return std::min(this->topUR.x(), this->botLL.x());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto maxX() const -> T
    {
      return std::max(this->topUR.x(), this->botLL.x());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto minY() const -> T
    {
      return std::min(this->topUR.y(), this->botLL.y());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto maxY() const -> T
    {
      return std::max(this->topUR.y(), this->botLL.y());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto minZ() const -> T
    {
      return std::min(this->topUR.z(), this->botLL.z());
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto maxZ() const -> T
    {
      return std::max(this->topUR.z(), this->botLL.z());
    }

  private:
    vec3<T> topUR{};
    vec3<T> botLL{};
  };
}
