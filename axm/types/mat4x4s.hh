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
    constexpr static size_t MAX_INDEX = 15;
    vec4<vec4<T>> data{};

    /// mat4x4s are useful for a number of non-numeric things, such as convolution filters (like resampling),
    /// so we don't want to assume what T will be
    mat4x4() requires(!IsNumeric<T>) = default;

    /// When using a mat4x4 with numeric values, we want to set the matrix to identity
    mat4x4() requires(IsNumeric<T>) : data({T(1), T(0), T(0), T(0)},
                                           {T(0), T(1), T(0), T(0)},
                                           {T(0), T(0), T(1), T(0)},
                                           {T(0), T(0), T(0), T(1)}) {}

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

    auto operator [] (const size_t index) -> vec4<T>&
    {
      if(index > MAX_INDEX)
      {
        return this->getSentinel();
      }
      return this->data[index];
    }

    auto operator [] (const size_t index) const -> vec4<T>
    {
      if(index > MAX_INDEX)
      {
        return {};
      }
      return this->data[index];
    }

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

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator == (const mat4x4& other) const -> bool
    {
      return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2] && this->data[3] == other.data[3];
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (T val) const -> mat4x4 requires(MathStorageType<T>)
    {
      return
      {
        {this->x1() * val, this->y1() * val, this->z1() * val, this->w1() * val},
        {this->x2() * val, this->y2() * val, this->z2() * val, this->w2() * val},
        {this->x3() * val, this->y3() * val, this->z3() * val, this->w3() * val},
        {this->x4() * val, this->y4() * val, this->z4() * val, this->w4() * val}
      };
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const mat4x4& other) const -> mat4x4 requires(MathStorageType<T>)
    {
      return
      {
        {
          this->x1() * other.x1() + this->x2() * other.y1() + this->x3() * other.z1() + this->x4() * other.w1(), //0, 0
          this->y1() * other.x1() + this->y2() * other.y1() + this->y3() * other.z1() + this->y4() * other.w1(), //0, 1
          this->z1() * other.x1() + this->z2() * other.y1() + this->z3() * other.z1() + this->z4() * other.w1(), //0, 2
          this->w1() * other.x1() + this->w2() * other.y1() + this->w3() * other.z1() + this->w4() * other.w1(), //0, 3
        },
        {
          this->x1() * other.x2() + this->x2() * other.y2() + this->x3() * other.z2() + this->x4() * other.w2(), //1, 0
          this->y1() * other.x2() + this->y2() * other.y2() + this->y3() * other.z2() + this->y4() * other.w2(), //1, 1
          this->z1() * other.x2() + this->z2() * other.y2() + this->z3() * other.z2() + this->z4() * other.w2(), //1, 2
          this->w1() * other.x2() + this->w2() * other.y2() + this->w3() * other.z2() + this->w4() * other.w2(), //1, 3
        },
        {
          this->x1() * other.x3() + this->x2() * other.y3() + this->x3() * other.z3() + this->x4() * other.w3(), //2, 0
          this->y1() * other.x3() + this->y2() * other.y3() + this->y3() * other.z3() + this->y4() * other.w3(), //2, 1
          this->z1() * other.x3() + this->z2() * other.y3() + this->z3() * other.z3() + this->z4() * other.w3(), //2, 2
          this->w1() * other.x3() + this->w2() * other.y3() + this->w3() * other.z3() + this->w4() * other.w3(), //2, 3
        },
        {
          this->x1() * other.x4() + this->x2() * other.y4() + this->x3() * other.z4() + this->x4() * other.w4(), //3, 0
          this->y1() * other.x4() + this->y2() * other.y4() + this->y3() * other.z4() + this->y4() * other.w4(), //3, 1
          this->z1() * other.x4() + this->z2() * other.y4() + this->z3() * other.z4() + this->z4() * other.w4(), //3, 2
          this->w1() * other.x4() + this->w2() * other.y4() + this->w3() * other.z4() + this->w4() * other.w4(), //3, 3
        }
      };
    }

    GNUCONST USE_RESULT CANNOT_FAIL
    auto operator * (const vec4<T>& vec) const -> vec4<T> requires(MathStorageType<T>)
    {
      return
      {
        vec.x() * this->x1() + vec.y() * this->y1() + vec.z() * this->z1() + vec.w() * this->w1(),
        vec.x() * this->x2() + vec.y() * this->y2() + vec.z() * this->z2() + vec.w() * this->w2(),
        vec.x() * this->x3() + vec.y() * this->y3() + vec.z() * this->z3() + vec.w() * this->w3(),
        vec.x() * this->x4() + vec.y() * this->y4() + vec.z() * this->z4() + vec.w() * this->w4(),
      };
    }

    auto print(const std::string& pre = "") const -> void requires(ConvertibleToString<T>)
    {
      printf("mat4x4: %s\n", pre.c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x1()).c_str(), std::to_string(this->y1()).c_str(), std::to_string(this->z1()).c_str(), std::to_string(this->w1()).c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x2()).c_str(), std::to_string(this->y2()).c_str(), std::to_string(this->z2()).c_str(), std::to_string(this->w2()).c_str());
      printf(" [%s, %s, %s, %s]\n",   std::to_string(this->x3()).c_str(), std::to_string(this->y3()).c_str(), std::to_string(this->z3()).c_str(), std::to_string(this->w3()).c_str());
      printf(" [%s, %s, %s, %s]\n\n", std::to_string(this->x4()).c_str(), std::to_string(this->y4()).c_str(), std::to_string(this->z4()).c_str(), std::to_string(this->w4()).c_str());
    }

  private:
    auto getSentinel() -> vec4<T>&
    {
      static vec4<T> sentinel{};
      sentinel = vec4<T>();
      return sentinel;
    }
  };
}
