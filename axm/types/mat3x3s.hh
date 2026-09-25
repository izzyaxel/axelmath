#pragma once

#include "vec3s.hh"

#include <string>

//TODO Conversion operators, constructors, etc

namespace axm
{

  /// A 3x3 matrix
  /// Column-major by default, but can be transposed into row-major
  /// @tparam T Any type or class supporting the == (equivalence) operator and all basic math operators (+ - * /), plain numeric types will cause the matrix to be initialized to identity
  template<MathStorageType T>
  struct mat3x3
  {
    constexpr static size_t MAX_INDEX = 8;
    vec3<vec3<T>> data;

    mat3x3() requires(!IsNumeric<T>) = default;

    /// When using a mat4x4 with numeric values, we want to set the matrix to identity
    mat3x3() requires(IsNumeric<T>) : data({1, 0, 0},
                                           {0, 1, 0},
                                           {0, 0, 1}) {}

    mat3x3(
      const T x1, const T y1, const T z1,
      const T x2, const T y2, const T z2,
      const T x3, const T y3, const T z3
      ) : data({x1, y1, z1},
               {x2, y2, z2},
               {x3, y3, z3}) {}

    mat3x3(const vec3<T>& column0, const vec3<T>& column1, const vec3<T>& column2) : data(column0, column1, column2) {}

    mat3x3(mat3x3&& other) noexcept = default;
    mat3x3(const mat3x3& other) = default;
    auto operator = (const mat3x3& other) -> mat3x3& = default;
    auto operator = (mat3x3&& other) noexcept -> mat3x3& = default;

    auto operator [] (const size_t index) -> vec3<T>&
    {
      if(index > MAX_INDEX)
      {
        return this->getSentinel();
      }
      return this->data[index];
    }

    auto operator [] (const size_t index) const -> vec3<T>
    {
      if(index > MAX_INDEX)
      {
        return {};
      }
      return this->data[index];
    }

    //Value Access
    GNUCONST USE_RESULT CANNOT_FAIL auto x1() const -> T {return this->data[0][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y1() const -> T {return this->data[0][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z1() const -> T {return this->data[0][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto x2() const -> T {return this->data[1][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y2() const -> T {return this->data[1][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z2() const -> T {return this->data[1][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto x3() const -> T {return this->data[2][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y3() const -> T {return this->data[2][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z3() const -> T {return this->data[2][2];}
    USE_RESULT CANNOT_FAIL          auto x1() -> T& {return this->data[0][0];}
    USE_RESULT CANNOT_FAIL          auto y1() -> T& {return this->data[0][1];}
    USE_RESULT CANNOT_FAIL          auto z1() -> T& {return this->data[0][2];}
    USE_RESULT CANNOT_FAIL          auto x2() -> T& {return this->data[1][0];}
    USE_RESULT CANNOT_FAIL          auto y2() -> T& {return this->data[1][1];}
    USE_RESULT CANNOT_FAIL          auto z2() -> T& {return this->data[1][2];}
    USE_RESULT CANNOT_FAIL          auto x3() -> T& {return this->data[2][0];}
    USE_RESULT CANNOT_FAIL          auto y3() -> T& {return this->data[2][1];}
    USE_RESULT CANNOT_FAIL          auto z3() -> T& {return this->data[2][2];}

    //Column Access
    GNUCONST USE_RESULT CANNOT_FAIL auto col0() const -> vec3<T> {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto col1() const -> vec3<T> {return this->data[1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto col2() const -> vec3<T> {return this->data[2];}
    USE_RESULT CANNOT_FAIL          auto col0() -> vec3<T>& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto col1() -> vec3<T>& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto col2() -> vec3<T>& {return this->data[2];}

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator == (const mat3x3& other) const -> bool requires(HasEquivalenceOperator<T>)
    {
      return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (T val) const -> mat3x3 requires(HasMathOperators<T>)
    {
      return
      {
        {this->x1() * val, this->y1() * val, this->z1() * val},
        {this->x2() * val, this->y2() * val, this->z2() * val},
        {this->x3() * val, this->y3() * val, this->z3() * val}
      };
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const mat3x3& other) const -> mat3x3 requires(HasMathOperators<T>)
    {
      return
      {
        {
          this->x1() * other.x1() + this->x2() * other.y1() + this->x3() * other.z1(), //0, 0
          this->y1() * other.x1() + this->y2() * other.y1() + this->y3() * other.z1(), //0, 1
          this->z1() * other.x1() + this->z2() * other.y1() + this->z3() * other.z1(), //0, 2
        },
        {
          this->x1() * other.x2() + this->x2() * other.y2() + this->x3() * other.z2(), //1, 0
          this->y1() * other.x2() + this->y2() * other.y2() + this->y3() * other.z2(), //1, 1
          this->z1() * other.x2() + this->z2() * other.y2() + this->z3() * other.z2(), //1, 2
        },
        {
          this->x1() * other.x3() + this->x2() * other.y3() + this->x3() * other.z3(), //2, 0
          this->y1() * other.x3() + this->y2() * other.y3() + this->y3() * other.z3(), //2, 1
          this->z1() * other.x3() + this->z2() * other.y3() + this->z3() * other.z3(), //2, 2
        }
      };
    }

    auto print(const std::string& pre = "") const -> void requires(ConvertibleToString<T>)
    {
      printf("mat3x3: %s\n", pre.c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x1()).c_str(), std::to_string(this->y1()).c_str(), std::to_string(this->z1()).c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x2()).c_str(), std::to_string(this->y2()).c_str(), std::to_string(this->z2()).c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x3()).c_str(), std::to_string(this->y3()).c_str(), std::to_string(this->z3()).c_str());
    }

  private:
    vec3<T> sentinel{};
    auto getSentinel() -> vec3<T>&
    {
      this->sentinel = vec3<T>();
      return this->sentinel;
    }
  };
}