#pragma once

#include "vec4s.hh"

#include <numbers>

namespace axm
{

  /// A quaternion
  /// Immutable
  /// 4-dimensional representation of rotation that's immune to gimbal lock, and can be oriented in any direction
  /// @tparam T Any type or class supporting the == (equivalence) operator, and all basic math operators (+ - * /), plain numeric types will be handled slightly differently
  template <MathStorageType T>
  struct quat
  {
    /// X Y Z W, init to identity
    const T data[4]{0, 0, 0, 1};

    constexpr quat() = default;

    constexpr explicit quat(const quat& other) = default;

    // Convert a quaternion of another storage type
    template <typename Q>
    constexpr explicit quat(const quat<Q>& other) : data{other.data} {}

    /// Construct a quaternion out of given values
    constexpr quat(const T xIn, const T yIn, const T zIn, const T wIn) : data{xIn, yIn, zIn, wIn} {}

    quat(quat&& other) noexcept = default;

    auto operator = (const quat& other) -> quat&
    {
      if(*this != other)
      {
        this->~quat();
        ::new(this)quat(other);
      }
      return *this;
    }

    auto operator = (quat&& other) noexcept -> quat&
    {
      if(*this != other)
      {
        this->~quat();
        ::new(this)quat(other);
        other.~quat();
      }
      return *this;
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator [] (size_t index) const -> T
    {
      if(index > 3)
      {
        return {};
      }

      return this->data[index];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto x() const -> T
    {
      return this->data[0];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto y() const -> T
    {
      return this->data[1];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto z() const -> T
    {
      return this->data[2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto w() const -> T
    {
      return this->data[3];
    }

    CONST USE_RESULT CANNOT_FAIL
    bool operator == (const quat& other) const
    {
      return this->data[0] == other[0] && this->data[1] == other[1] && this->data[2] == other[2] && this->data[3] == other[3];
    }

    CONST USE_RESULT CANNOT_FAIL
    quat operator + (const quat& other) const
    {
      return quat
      {
        this->data[0] + other.data[0],
        this->data[1] + other.data[1],
        this->data[2] + other.data[2],
        this->data[3] + other.data[3]};
    }

    CONST USE_RESULT CANNOT_FAIL
    quat operator * (const float val) const
    {
      return quat
      {
        this->data[0] * val,
        this->data[1] * val,
        this->data[2] * val,
        this->data[3] * val};
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const quat& other) const -> quat
    {
      return quat
      {
        ( this->data[0] * other[3] + this->data[1] * other[2] - this->data[2] * other[1] + this->data[3] * other[0]),
        (-this->data[0] * other[2] + this->data[1] * other[3] + this->data[2] * other[0] + this->data[3] * other[1]),
        ( this->data[0] * other[1] - this->data[1] * other[0] + this->data[2] * other[3] + this->data[3] * other[2]),
        (-this->data[0] * other[0] - this->data[1] * other[1] - this->data[2] * other[2] + this->data[3] * other[3])
      }.normalized();
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const vec3<T>& other) const -> vec3<T>
    {
      const vec3<T> q = {this->data[0], this->data[1], this->data[2]};
      const vec3<T> c = other.cross(q);
      const vec3<T> w1 = c * (T)2;
      return other + w1 * this->data[3] + w1.cross(q);
    }

    CONST USE_RESULT CANNOT_FAIL
    auto conjugated() const -> quat
    {
      return quat{-this->data[0], -this->data[1], -this->data[2], this->data[3]};
    }

    /// Get the magnitude(length) of this quaternion
    CONST USE_RESULT CANNOT_FAIL
    auto mag() const -> T
    {
      return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2] + this->data[3] * this->data[3]);
    }

    /// Make a unit length version of this quaternion
    CONST USE_RESULT CANNOT_FAIL
    auto normalized() const -> quat
    {
      T length = this->mag();
      return quat{this->data[0] / length, this->data[1] / length, this->data[2] / length, this->data[3] / length};
    }

    /// Find the dot product of this quaternion
    CONST USE_RESULT CANNOT_FAIL
    auto dot(const quat& other) const -> T
    {
      return this->data[3] * other[3] + this->data[0] * other[0] + this->data[1] * other[1] + this->data[2] * other[2];
    }

    /// Get the inverse of this quaternion
    CONST USE_RESULT CANNOT_FAIL
    auto inverse() const -> quat
    {
      const T length = this->mag();
      return quat{-this->data[0] / length, -this->data[1] / length, -this->data[2] / length, this->data[3] / length};
    }

    /// Convert this quaternion into euler angles
    /// @return {roll pitch yaw} in radians
    CONST USE_RESULT CANNOT_FAIL
    auto toEulerRotation() const -> vec3<T>
    {
      constexpr T one = (T)1;
      constexpr T two = (T)2;
      const T sinr = two * (this->w() * this->x() + this->y() * this->z());
      const T cosr = one - (two * (this->x() * this->x() + this->y() * this->y()));
      const T roll = std::atan2(sinr, cosr);
      const T sinp = two * (this->w() * this->y() - this->z() * this->x());
      const T siny = two * (this->w() * this->z() + this->x() * this->y());
      const T cosy = one - (two * (this->y() * this->y() + this->z() * this->z()));
      const T yaw = std::atan2(siny, cosy);

      if(std::fabs(sinp) >= 1)
      {
        return {roll, std::copysign(std::numbers::pi / two, sinp), yaw};
      }

      return {roll, std::asin(sinp), yaw};
    }

    /// Convert this quaternion to an axis + angle rotation
    /// @return {x, y, z, radians}
    CONST USE_RESULT CANNOT_FAIL
    auto toAxial() const -> vec4<T>
    {
      const float angle = (T)2 * std::acos(this->w());
      const float divisor = std::sqrt(1 - (this->w() * this->w()));

      if(divisor < 0.001f)
      {
        return {this->x(), this->y(), this->z(), angle};
      }

      return {this->x() / divisor, this->y() / divisor, this->z() / divisor, angle};
    }

    constexpr static auto size() -> size_t
    {
      return 4;
    }

    /// Get a formatted string of the contents of this quaternion
    [[nodiscard]] auto toString() const -> std::string
    {
      std::string out = "(quat)\n[";
      for(int i = 0; i < 4; i++)
      {
        switch(i)
        {
          case 0:
            out += "x: ";
            break;
          case 1:
            out += "y: ";
            break;
          case 2:
            out += "z: ";
            break;
          case 3:
            out += "w: ";
            break;
          default: break;
        }
        out += std::to_string(this->data[i]);
        if(i < 3) out += ' ';
      }
      out += "]\n";
      return out;
    }

    /// Print this quaternion with printf
    void print(const std::string& name) const
    {
      printf("%s: %s\n", name.data(), this->toString().data());
    }
  };
}
