#pragma once

#include "vec4s.hh"

#include "../aliases.hh"
#include "../concepts.hh"

namespace axm
{

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

    template <typename U>
    constexpr explicit quat(const quat<U>& other)
    {
      this->x() = (T)other.x();
      this->y() = (T)other.y();
      this->z() = (T)other.z();
      this->w() = (T)other.w();
    }

    constexpr quat(const T xIn, const T yIn, const T zIn, const T wIn) : data{xIn, yIn, zIn, wIn} {}

    quat(quat&& other) noexcept
    {
      if(this != &other)
      {
        this->data = other.data;
        other.data = {};
      }
    }

    quat(const quat& other)
    {
      if(this != &other)
      {
        this->data = other.data;
      }
    }

    GNUCONST USE_RESULT CANNOT_FAIL auto x() const -> T {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y() const -> T {return this->data[1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z() const -> T {return this->data[2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto w() const -> T {return this->data[3];}
    USE_RESULT CANNOT_FAIL          auto x() -> T& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto y() -> T& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto z() -> T& {return this->data[2];}
    USE_RESULT CANNOT_FAIL          auto w() -> T& {return this->data[3];}

    USE_RESULT CANNOT_FAIL          auto operator [] (size_t index) -> T&;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> T;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const quat& other) const -> bool requires(HasEquivalenceOperator<T>);
    CANNOT_FAIL                     auto operator += (const quat& other) -> quat requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator *= (float val) -> quat requires(IsNumeric<T>);
    CANNOT_FAIL                     auto operator *= (const quat& other) -> quat requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator + (const quat& other) const -> quat requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (float val) const -> quat requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const quat& other) const -> quat requires(IsNumeric<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const vec3<T>& other) const -> vec3<T> requires(IsNumeric<T>);

    constexpr static auto size() -> size_t
    {
      return 4;
    }

    /// Get a formatted string of the contents of this quaternion
    GNUCONST USE_RESULT CANNOT_FAIL
    auto toString() const -> std::string requires(ConvertibleToString<T>)
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
    auto print(const std::string& name) const -> void requires(ConvertibleToString<T>)
    {
      printf("quat %s: %s\n", name.data(), this->toString().data());
    }
  };
}
