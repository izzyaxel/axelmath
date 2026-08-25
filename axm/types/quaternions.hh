#pragma once

#include "../aliases.hh"
#include "../concepts.hh"

#include <string>
#include <numbers>
#include <cmath>

namespace axm
{

  template <typename T>
  struct vec3;

  template <typename T>
  struct vec4;

  /// A quaternion
  /// 4-dimensional representation of rotation that's immune to gimbal lock, and can be oriented in any direction
  /// Most useful for representing rotation in microgravity, but can be used for any kind of rotation
  /// @tparam T Any type or class supporting the == (equivalence) operator, and all basic math operators (+ - * /), plain numeric types will be handled slightly differently
  template <MathStorageType T>
  struct quat
  {
    /// X Y Z W, init to identity
    std::array<T, 4> data{0, 0, 0, 1};

    constexpr quat() = default;

    template <typename Q>
    constexpr explicit quat(const quat<Q>& other)
    {
      this->x() = (T)other.x();
      this->y() = (T)other.y();
      this->z() = (T)other.z();
      this->w() = (T)other.w();
    }

    constexpr quat(const T xIn, const T yIn, const T zIn, const T wIn) : data{xIn, yIn, zIn, wIn} {}

    //==Move============================================================================================================

    quat(quat&& other) noexcept
    {
      if(this != &other)
      {
        this->data = other.data;
        other.data = {};
      }
    }

    auto operator = (quat&& other) noexcept -> quat&
    {
      if(this != &other)
      {
        this->data = other.data;
        other.data = {};
      }
      return *this;
    }

    //==Copy============================================================================================================

    quat(const quat& other)
    {
      if(this != &other)
      {
        this->data = other.data;
      }
    }

    auto operator = (const quat& other) -> quat&
    {
      if(this != &other)
      {
        this->data = other.data;
      }
      return *this;
    }

    //==Accessors=======================================================================================================

    USE_RESULT CANNOT_FAIL
    auto operator [] (size_t index) -> T&
    {
      if(index > 3)
      {
        return {};
      }

      return this->data[index];
    }

    USE_RESULT CANNOT_FAIL
    auto x() -> T&
    {
      return this->data[0];
    }

    USE_RESULT CANNOT_FAIL
    auto y() -> T&
    {
      return this->data[1];
    }

    USE_RESULT CANNOT_FAIL
    auto z() -> T&
    {
      return this->data[2];
    }

    USE_RESULT CANNOT_FAIL
    auto w() -> T&
    {
      return this->data[3];
    }

    //==Const Accessors=================================================================================================

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator [] (size_t index) const -> T
    {
      if(index > 3)
      {
        return {};
      }

      return this->data[index];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto x() const -> T
    {
      return this->data[0];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto y() const -> T
    {
      return this->data[1];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto z() const -> T
    {
      return this->data[2];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto w() const -> T
    {
      return this->data[3];
    }

    //==Equivalence=====================================================================================================

    GNUCONST USE_RESULT CANNOT_FAIL
    bool operator == (const quat& other) const
    {
      return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
    }

    //==Math Operators==================================================================================================

    USE_RESULT CANNOT_FAIL
    quat operator + (const quat& other)
    {
      this->x() += other.x();
      this->y() += other.y();
      this->z() += other.z();
      this->w() += other.w();
      return *this;
    }

    USE_RESULT CANNOT_FAIL
    quat operator * (const float val)
    {
      this->x() *= val;
      this->y() *= val;
      this->z() *= val;
      this->w() *= val;
      return *this;
    }

    USE_RESULT CANNOT_FAIL
    auto operator * (const quat& other) -> quat
    {
      this->x() =  this->x() * other.w() + this->y() * other.z() - this->z() * other.y() + this->w() * other.x();
      this->y() = -this->x() * other.z() + this->y() * other.w() + this->z() * other.x() + this->w() * other.y();
      this->z() =  this->x() * other.y() - this->y() * other.x() + this->z() * other.w() + this->w() * other.z();
      this->w() = -this->x() * other.x() - this->y() * other.y() - this->z() * other.z() + this->w() * other.w();
      this->normalize();
      return *this;
    }

    //==Const Math Operators============================================================================================

    GNUCONST USE_RESULT CANNOT_FAIL
    quat operator + (const quat& other) const
    {
      return quat
      {
        this->x() + other.x(),
        this->y() + other.y(),
        this->z() + other.z(),
        this->w() + other.w()};
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    quat operator * (const float val) const
    {
      return quat
      {
        this->x() * val,
        this->y() * val,
        this->z() * val,
        this->w() * val
      };
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const quat& other) const -> quat
    {
      return quat
      {
         this->x() * other.w() + this->y() * other.z() - this->z() * other.y() + this->w() * other.x(),
        -this->x() * other.z() + this->y() * other.w() + this->z() * other.x() + this->w() * other.y(),
         this->x() * other.y() - this->y() * other.x() + this->z() * other.w() + this->w() * other.z(),
        -this->x() * other.x() - this->y() * other.y() - this->z() * other.z() + this->w() * other.w()
      }.normalized();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const vec3<T>& other) const -> vec3<T>
    {
      const vec3<T> q = {this->x(), this->y(), this->z()};
      const vec3<T> c = other.cross(q);
      const vec3<T> w1 = c * (T)2;
      return other + w1 * this->w() + w1.cross(q);
    }

    //==Math============================================================================================================

    CANNOT_FAIL
    auto conjugate() -> void
    {
      this->x() = -this->x();
      this->y() = -this->y();
      this->z() = -this->z();
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto conjugated() const -> quat
    {
      return quat{-this->x(), -this->y(), -this->z(), this->w()};
    }

    /// Get the magnitude(length) of this quaternion
    GNUCONST USE_RESULT CANNOT_FAIL
    auto mag() const -> T
    {
      return std::sqrt(this->x() * this->x() + this->y() * this->y() + this->z() * this->z() + this->w() * this->w());
    }

    /// Make this quaternion unit length
    CANNOT_FAIL
    auto normalize() -> void
    {
      T length = this->mag();
      this->x() /= length;
      this->y() /= length;
      this->z() /= length;
      this->w() /= length;
    }

    /// Make a unit length version of this quaternion
    GNUCONST USE_RESULT CANNOT_FAIL
    auto normalized() const -> quat
    {
      T length = this->mag();
      return quat{this->x() / length, this->y() / length, this->z() / length, this->w() / length};
    }

    /// Find the dot product of this quaternion
    GNUCONST USE_RESULT CANNOT_FAIL
    auto dot(const quat& other) const -> T
    {
      return this->w() * other.w() + this->x() * other.x() + this->y() * other.y() + this->z() * other.z();
    }

    /// Invert this quaternion
    CANNOT_FAIL
    auto invert() -> void
    {
      this->conjugate();
      this->normalize();
    }

    /// Get the inverse of this quaternion
    GNUCONST USE_RESULT CANNOT_FAIL
    auto inverse() const -> quat
    {
      quat out{this->x(), this->y(), this->z(), this->w()};
      out.conjugate();
      out.normalize();
      return out;
    }

    //==Conversions=====================================================================================================

    /// Convert this quaternion into euler angles
    /// @return {roll pitch yaw} in radians
    GNUCONST USE_RESULT CANNOT_FAIL
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
    GNUCONST USE_RESULT CANNOT_FAIL
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

    //==Misc============================================================================================================

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
