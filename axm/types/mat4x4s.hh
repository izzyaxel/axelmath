#pragma once

#include "vec4s.hh"

#include <string>

namespace axm
{

  /// A 4x4 matrix
  /// Column-major by default, but can be transposed into row-major
  /// Uses math notation for the locations of values, eg: x1 = [0][0], z4 = [3][2], etc
  /// @tparam T Any type or class supporting the == (equivalence) operator and all basic math operators (+ - * /), plain numeric types will cause the matrix to be initialized to identity
  template <MathStorageType T>
  struct mat4x4
  {
    vec4<vec4<T>> data{};

    /// mat4x4s are useful for a number of non-numeric things, such as convolution filters (like resampling),
    /// so we don't want to assume what T will be
    mat4x4() requires(!IsNumeric<T>) = default;

    /// When using a mat4x4 with numeric values, we want to set the matrix to identity
    mat4x4() requires(IsNumeric<T>) : data({(T)1, (T)0, (T)0, (T)0},
                                           {(T)0, (T)1, (T)0, (T)0},
                                           {(T)0, (T)0, (T)1, (T)0},
                                           {(T)0, (T)0, (T)0, (T)1}) {}

    mat4x4(
      const T x1, const T y1, const T z1, const T w1,
      const T x2, const T y2, const T z2, const T w2,
      const T x3, const T y3, const T z3, const T w3,
      const T x4, const T y4, const T z4, const T w4
      ) : data({x1, y1, z1, w1},
               {x2, y2, z2, w2},
               {x3, y3, z3, w3},
               {x4, y4, z4, w4}) {}

    mat4x4(const vec4<T>& column0, const vec4<T>& column1, const vec4<T>& column2, const vec4<T>& column3) : data(column0, column1, column2, column3) {}
    
    mat4x4(mat4x4&& other) noexcept = default;
    mat4x4(const mat4x4& other) = default;
    auto operator = (const mat4x4& other) -> mat4x4& = default;
    auto operator = (mat4x4&& other) noexcept -> mat4x4& = default;

    //Value access
    GNUCONST USE_RESULT CANNOT_FAIL auto x1() const -> T {return this->data[0][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y1() const -> T {return this->data[0][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z1() const -> T {return this->data[0][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto w1() const -> T {return this->data[0][3];}
    GNUCONST USE_RESULT CANNOT_FAIL auto x2() const -> T {return this->data[1][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y2() const -> T {return this->data[1][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z2() const -> T {return this->data[1][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto w2() const -> T {return this->data[1][3];}
    GNUCONST USE_RESULT CANNOT_FAIL auto x3() const -> T {return this->data[2][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y3() const -> T {return this->data[2][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z3() const -> T {return this->data[2][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto w3() const -> T {return this->data[2][3];}
    GNUCONST USE_RESULT CANNOT_FAIL auto x4() const -> T {return this->data[3][0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto y4() const -> T {return this->data[3][1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto z4() const -> T {return this->data[3][2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto w4() const -> T {return this->data[3][3];}
    USE_RESULT CANNOT_FAIL          auto x1() -> T& {return this->data[0][0];}
    USE_RESULT CANNOT_FAIL          auto y1() -> T& {return this->data[0][1];}
    USE_RESULT CANNOT_FAIL          auto z1() -> T& {return this->data[0][2];}
    USE_RESULT CANNOT_FAIL          auto w1() -> T& {return this->data[0][3];}
    USE_RESULT CANNOT_FAIL          auto x2() -> T& {return this->data[1][0];}
    USE_RESULT CANNOT_FAIL          auto y2() -> T& {return this->data[1][1];}
    USE_RESULT CANNOT_FAIL          auto z2() -> T& {return this->data[1][2];}
    USE_RESULT CANNOT_FAIL          auto w2() -> T& {return this->data[1][3];}
    USE_RESULT CANNOT_FAIL          auto x3() -> T& {return this->data[2][0];}
    USE_RESULT CANNOT_FAIL          auto y3() -> T& {return this->data[2][1];}
    USE_RESULT CANNOT_FAIL          auto z3() -> T& {return this->data[2][2];}
    USE_RESULT CANNOT_FAIL          auto w3() -> T& {return this->data[2][3];}
    USE_RESULT CANNOT_FAIL          auto x4() -> T& {return this->data[3][0];}
    USE_RESULT CANNOT_FAIL          auto y4() -> T& {return this->data[3][1];}
    USE_RESULT CANNOT_FAIL          auto z4() -> T& {return this->data[3][2];}
    USE_RESULT CANNOT_FAIL          auto w4() -> T& {return this->data[3][3];}

    //Column access
    GNUCONST USE_RESULT CANNOT_FAIL auto col0() const -> vec4<T> {return this->data[0];}
    GNUCONST USE_RESULT CANNOT_FAIL auto col1() const -> vec4<T> {return this->data[1];}
    GNUCONST USE_RESULT CANNOT_FAIL auto col2() const -> vec4<T> {return this->data[2];}
    GNUCONST USE_RESULT CANNOT_FAIL auto col3() const -> vec4<T> {return this->data[3];}
    USE_RESULT CANNOT_FAIL          auto col0() -> vec4<T>& {return this->data[0];}
    USE_RESULT CANNOT_FAIL          auto col1() -> vec4<T>& {return this->data[1];}
    USE_RESULT CANNOT_FAIL          auto col2() -> vec4<T>& {return this->data[2];}
    USE_RESULT CANNOT_FAIL          auto col3() -> vec4<T>& {return this->data[3];}

    //TODO other operators?
    GNUCONST USE_RESULT CANNOT_FAIL auto operator == (const mat4x4& other) const -> bool;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator [] (size_t index) const -> vec4<T>;
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (T val) const -> mat4x4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const mat4x4& other) const -> mat4x4 requires(MathStorageType<T>);
    GNUCONST USE_RESULT CANNOT_FAIL auto operator * (const vec4<T>& vec) const -> vec4<T> requires(MathStorageType<T>);

    auto print(const std::string& msg) const -> void requires(ConvertibleToString<T>)
    {
      printf("mat4x4: %s\n", msg.c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x1()).c_str(), std::to_string(this->y1()).c_str(), std::to_string(this->z1()).c_str(), std::to_string(this->w1()).c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x2()).c_str(), std::to_string(this->y2()).c_str(), std::to_string(this->z2()).c_str(), std::to_string(this->w2()).c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x3()).c_str(), std::to_string(this->y3()).c_str(), std::to_string(this->z3()).c_str(), std::to_string(this->w3()).c_str());
      printf(" [%s, %s, %s, %s]\n\n", std::to_string(this->x4()).c_str(), std::to_string(this->y4()).c_str(), std::to_string(this->z4()).c_str(), std::to_string(this->w4()).c_str());
    }
  };
}