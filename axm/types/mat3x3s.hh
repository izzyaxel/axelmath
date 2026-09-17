#pragma once

#include "vec3s.hh"

#include <string>

namespace axm
{

  /// A 3x3 matrix
  /// Column-major by default, but can be transposed into row-major
  /// @tparam T Any type or class supporting the == (equivalence) operator and all basic math operators (+ - * /), plain numeric types will cause the matrix to be initialized to identity
  template<MathStorageType T>
  struct mat3x3
  {
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

    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const mat3x3& other) const -> bool requires(HasEquivalenceOperator<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> vec3<T>;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (T val) const -> mat3x3 requires(HasMathOperators<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const mat3x3& other) const -> mat3x3 requires(HasMathOperators<T>);

    auto print(const std::string& msg) const -> void requires(ConvertibleToString<T>)
    {
      printf("mat3x3: %s\n", msg.c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x1()).c_str(), std::to_string(this->y1()).c_str(), std::to_string(this->z1()).c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x2()).c_str(), std::to_string(this->y2()).c_str(), std::to_string(this->z2()).c_str());
      printf(" [%s %s %s]\n",   std::to_string(this->x3()).c_str(), std::to_string(this->y3()).c_str(), std::to_string(this->z3()).c_str());
    }
  };
}
