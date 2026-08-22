#pragma once

#include "../aliases.hh"
#include "../concepts.hh"

#include "vec4s.hh"

namespace axm
{

  template <MathStorageType T>
  struct quat;

  /// A 4x4 matrix
  /// Immutable
  /// Column-major by default, but can be transposed into row-major
  /// @tparam T Any type or class supporting the == (equivalence) operator and all basic math operators (+ - * /), plain numeric types will cause the matrix to be initialized to identity
  template <MathStorageType T>
  struct mat4x4
  {
    const vec4<vec4<T>> data{};

    /// mat4x4s are useful for a number of things such as convolution filters (like resampling), where you want to
    /// store non-numeric values, so we don't want to assume what T is
    mat4x4() requires(!IsNumeric<T>) = default;

    /// When using a mat4x4 with numeric values, we want to set the matrix to identity
    mat4x4() requires(IsNumeric<T>) : data({1, 0, 0, 0},
                                           {0, 1, 0, 0},
                                           {0, 0, 1, 0},
                                           {0, 0, 0, 1}) {}

    mat4x4(const mat4x4& other) : data(other.data) {}

    mat4x4(mat4x4&& other) noexcept = default;

    auto operator = (const mat4x4& other) -> mat4x4&
    {
      if(this != &other)
      {
        this->~mat4x4();
        ::new(this)mat4x4(other);
      }
      return *this;
    }

    auto operator = (mat4x4&& other) noexcept -> mat4x4&
    {
      if(this != &other)
      {
        this->~mat4x4();
        ::new(this)mat4x4(other);
        other.~mat4x4();
      }
      return *this;
    }

    mat4x4(
      const T val00, const T val01, const T val02, const T val03, //Column 0
      const T val10, const T val11, const T val12, const T val13, //Column 1
      const T val20, const T val21, const T val22, const T val23, //Column 2
      const T val30, const T val31, const T val32, const T val33  //Column 3
      ) : data({val00, val01, val02, val03},
               {val10, val11, val12, val13},
               {val20, val21, val22, val23},
               {val30, val31, val32, val33}) {}

    mat4x4(const vec4<T>& column0, const vec4<T>& column1, const vec4<T>& column2, const vec4<T>& column3) : data(column0, column1, column2, column3) {}

    auto operator == (const mat4x4& other) const -> bool
    {
      return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2] && this->data[3] == other.data[3];
    }

    /// The primary method of accessing the contents of this matrix
    /// @param index 0-3, The column to retrieve
    /// @return The specified column, or an empty vec4 if the index was out of bounds
    CONST USE_RESULT CANNOT_FAIL
    auto operator [] (const size_t index) const -> vec4<T>
    {
      if(index > 3)
      {
        return {};
      }

      return this->data[index];
    }

    //Math notation accessors

    CONST USE_RESULT CANNOT_FAIL
    auto x1() const -> T
    {
      return this->data[0][0];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto y1() const -> T
    {
      return this->data[0][1];
    }

    CONST USE_RESULT CANNOT_FAIL
     auto z1() const -> T
    {
      return this->data[0][2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto w1() const -> T
    {
      return this->data[0][3];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto x2() const -> T
    {
      return this->data[1][0];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto y2() const -> T
    {
      return this->data[1][1];
    }

    CONST USE_RESULT CANNOT_FAIL
     auto z2() const -> T
    {
      return this->data[1][2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto w2() const -> T
    {
      return this->data[1][3];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto x3() const -> T
    {
      return this->data[2][0];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto y3() const -> T
    {
      return this->data[2][1];
    }

    CONST USE_RESULT CANNOT_FAIL
     auto z3() const -> T
    {
      return this->data[2][2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto w3() const -> T
    {
      return this->data[2][3];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto x4() const -> T
    {
      return this->data[3][0];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto y4() const -> T
    {
      return this->data[3][1];
    }

    CONST USE_RESULT CANNOT_FAIL
     auto z4() const -> T
    {
      return this->data[3][2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto w4() const -> T
    {
      return this->data[3][3];
    }

    /// Multiply each cell by a single value
    /// @return A mat4x4 containing the result
    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const T val) const -> mat4x4
    {
      return
      {
        {this->x1() * val, this->y1() * val, this->z1() * val, this->w1() * val},
        {this->x2() * val, this->y2() * val, this->z2() * val, this->w2() * val},
        {this->x3() * val, this->y3() * val, this->z3() * val, this->w3() * val},
        {this->x4() * val, this->y4() * val, this->z4() * val, this->w4() * val}
      };
    }

    /// Multiply this matrix by another
    /// @param other Another mat4x4 of the same storage type
    /// @return A mat4x4 containing the result
    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const mat4x4 other) const -> mat4x4
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

    /// Multiply this mat4x4 by a 4-component vector
    /// @param vec A vec4 of the same storage type as this mat4x4
    /// @return A mat4x4 containing the result
    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const vec4<T>& vec) const -> vec4<T>
    {
      return
      {
        vec.x() * this->x1() + vec.y() * this->y1() + vec.z() * this->z1() + vec.w() * this->w1(),
        vec.x() * this->x2() + vec.y() * this->y2() + vec.z() * this->z2() + vec.w() * this->w2(),
        vec.x() * this->x3() + vec.y() * this->y3() + vec.z() * this->z3() + vec.w() * this->w3(),
        vec.x() * this->x4() + vec.y() * this->y4() + vec.z() * this->z4() + vec.w() * this->w4(),
      };
    }

    /// Get a new mat4x4 with the given cell set to the given value
    CONST USE_RESULT CANNOT_FAIL
    auto set(const size_t column, const size_t row, T value) -> mat4x4
    {
      return
      {
        {
          column == 0 && row == 0 ? value : this->x1(),
          column == 0 && row == 1 ? value : this->y1(),
          column == 0 && row == 2 ? value : this->z1(),
          column == 0 && row == 3 ? value : this->w1()
        },

        {
          column == 1 && row == 0 ? value : this->x2(),
          column == 1 && row == 1 ? value : this->y2(),
          column == 1 && row == 2 ? value : this->z2(),
          column == 1 && row == 3 ? value : this->w2()
        },

        {
          column == 2 && row == 0 ? value : this->x3(),
          column == 2 && row == 1 ? value : this->y3(),
          column == 2 && row == 2 ? value : this->z3(),
          column == 2 && row == 3 ? value : this->w3()
        },

        {
          column == 3 && row == 0 ? value : this->x4(),
          column == 3 && row == 1 ? value : this->y4(),
          column == 3 && row == 2 ? value : this->z4(),
          column == 3 && row == 3 ? value : this->w4()
        }
      };
    }

    /// Calculate the determinant of this mat4x4
    /// @return The determinant value, in the storage type of this mat4x4
    CONST USE_RESULT CANNOT_FAIL
    auto determinant() const -> T
    {
      /*return
        this->data[0][3] * this->data[1][2] * this->data[2][1] * this->data[3][0] -
        this->data[0][2] * this->data[1][3] * this->data[2][1] * this->data[3][0] -
        this->data[0][3] * this->data[1][1] * this->data[2][2] * this->data[3][0] +
        this->data[0][1] * this->data[1][3] * this->data[2][2] * this->data[3][0] +
        this->data[0][2] * this->data[1][1] * this->data[2][3] * this->data[3][0] -
        this->data[0][1] * this->data[1][2] * this->data[2][3] * this->data[3][0] -
        this->data[0][3] * this->data[1][2] * this->data[2][0] * this->data[3][1] +
        this->data[0][2] * this->data[1][3] * this->data[2][0] * this->data[3][1] +
        this->data[0][3] * this->data[1][0] * this->data[2][2] * this->data[3][1] -
        this->data[0][0] * this->data[1][3] * this->data[2][2] * this->data[3][1] -
        this->data[0][2] * this->data[1][0] * this->data[2][3] * this->data[3][1] +
        this->data[0][0] * this->data[1][2] * this->data[2][3] * this->data[3][1] +
        this->data[0][3] * this->data[1][1] * this->data[2][0] * this->data[3][2] -
        this->data[0][1] * this->data[1][3] * this->data[2][0] * this->data[3][2] -
        this->data[0][3] * this->data[1][0] * this->data[2][1] * this->data[3][2] +
        this->data[0][0] * this->data[1][3] * this->data[2][1] * this->data[3][2] +
        this->data[0][1] * this->data[1][0] * this->data[2][3] * this->data[3][2] -
        this->data[0][0] * this->data[1][1] * this->data[2][3] * this->data[3][2] -
        this->data[0][2] * this->data[1][1] * this->data[2][0] * this->data[3][3] +
        this->data[0][1] * this->data[1][2] * this->data[2][0] * this->data[3][3] +
        this->data[0][2] * this->data[1][0] * this->data[2][1] * this->data[3][3] -
        this->data[0][0] * this->data[1][2] * this->data[2][1] * this->data[3][3] -
        this->data[0][1] * this->data[1][0] * this->data[2][2] * this->data[3][3] +
        this->data[0][0] * this->data[1][1] * this->data[2][2] * this->data[3][3];*/

      return
        this->w1() * this->z2() * this->y3() * this->x4() -
        this->z1() * this->w2() * this->y3() * this->x4() -
        this->w1() * this->y2() * this->z3() * this->x4() +
        this->y1() * this->w2() * this->z3() * this->x4() +
        this->z1() * this->y2() * this->w3() * this->x4() -
        this->y1() * this->z2() * this->w3() * this->x4() -
        this->w1() * this->z2() * this->x3() * this->y4() +
        this->z1() * this->w2() * this->x3() * this->y4() +
        this->w1() * this->x2() * this->z3() * this->y4() -
        this->x1() * this->w2() * this->z3() * this->y4() -
        this->z1() * this->x2() * this->w3() * this->y4() +
        this->x1() * this->z2() * this->w3() * this->y4() +
        this->w1() * this->y2() * this->x3() * this->z4() -
        this->y1() * this->w2() * this->x3() * this->z4() -
        this->w1() * this->x2() * this->y3() * this->z4() +
        this->x1() * this->w2() * this->y3() * this->z4() +
        this->y1() * this->x2() * this->w3() * this->z4() -
        this->x1() * this->y2() * this->w3() * this->z4() -
        this->z1() * this->y2() * this->x3() * this->w4() +
        this->y1() * this->z2() * this->x3() * this->w4() +
        this->z1() * this->x2() * this->y3() * this->w4() -
        this->x1() * this->z2() * this->y3() * this->w4() -
        this->y1() * this->x2() * this->z3() * this->w4() +
        this->x1() * this->y2() * this->z3() * this->w4();
    }

    /// Calculate the inverse of this mat4x4
    /// @return A mat4x4 containing the result
    CONST USE_RESULT CANNOT_FAIL
    auto inverse() const -> mat4x4
    {
      T a = this->z3() * this->w4() - this->w3() * this->z4();
      T b = this->y3() * this->w4() - this->w3() * this->y4();
      T c = this->y3() * this->z4() - this->z3() * this->y4();
      T d = this->x3() * this->w4() - this->w3() * this->x4();
      T e = this->x3() * this->z4() - this->z3() * this->x4();
      T f = this->x3() * this->y4() - this->y3() * this->x4();
      T g = this->z2() * this->w4() - this->w2() * this->z4();
      T h = this->y2() * this->w4() - this->w2() * this->y4();
      T i = this->y2() * this->z4() - this->z2() * this->y4();
      T j = this->z2() * this->w3() - this->w2() * this->z3();
      T k = this->y2() * this->w3() - this->w2() * this->y3();
      T l = this->y2() * this->z3() - this->z2() * this->y3();
      T m = this->x2() * this->w4() - this->w2() * this->x4();
      T n = this->x2() * this->z4() - this->z2() * this->x4();
      T o = this->x2() * this->w3() - this->w2() * this->x3();
      T p = this->x2() * this->z3() - this->z2() * this->x3();
      T q = this->x2() * this->y4() - this->y2() * this->x4();
      T r = this->x2() * this->y3() - this->y2() * this->x3();

      T det =   this->x1() * (this->y2() * a - this->z2() * b + this->w2() * c)
              - this->y1() * (this->x2() * a - this->z2() * d + this->w2() * e)
              + this->z1() * (this->x2() * b - this->y2() * d + this->w2() * f)
              - this->w1() * (this->x2() * c - this->y2() * e + this->z2() * f);
      det = (T)1 / det;

      return
      {
        {
          det *  (this->y2() * a - this->z2() * b + this->w2() * c),
          det * -(this->x2() * a - this->z2() * d + this->w2() * e),
          det *  (this->x2() * b - this->y2() * d + this->w2() * f),
          det * -(this->x2() * c - this->y2() * e + this->z2() * f)
        },

        {
          det * -(this->y1() * a - this->z1() * b + this->w1() * c),
          det *  (this->x1() * a - this->z1() * d + this->w1() * e),
          det * -(this->x1() * b - this->y1() * d + this->w1() * f),
          det *  (this->x1() * c - this->y1() * e + this->z1() * f)
        },
        {
          det *  (this->y1() * g - this->z1() * h + this->w1() * i),
          det * -(this->x1() * g - this->z1() * m + this->w1() * n),
          det *  (this->x1() * h - this->y1() * m + this->w1() * q),
          det * -(this->x1() * i - this->y1() * n + this->z1() * q)
        },
        {
          det * -(this->y1() * j - this->z1() * k + this->w1() * l),
          det *  (this->x1() * j - this->z1() * o + this->w1() * p),
          det * -(this->x1() * k - this->y1() * o + this->w1() * r),
          det *  (this->x1() * l - this->y1() * p + this->z1() * r)
        }
      };
    }

    /// Convert this matrix from column-major to row-major or vice-versa
    /// Be careful with this, keep track of which way each matrix is!
    /// @return A mat4x4 containing the result
    CONST USE_RESULT CANNOT_FAIL
    auto transposed() const -> mat4x4
    {
      return
      {
        {this->x1(), this->x2(), this->x3(), this->x4()},
        {this->y1(), this->y2(), this->y3(), this->y4()},
        {this->z1(), this->z2(), this->z3(), this->z4()},
        {this->w1(), this->w2(), this->w3(), this->w4()}
      };
    }

    auto print(const std::string& msg) const -> void
    {
      printf("mat4x4: %s\n", msg.c_str());
      printf(" [%f %f %f %f]\n",   (float)this->x1(), (float)this->y1(), (float)this->z1(), (float)this->w1());
      printf(" [%f %f %f %f]\n",   (float)this->x2(), (float)this->y2(), (float)this->z2(), (float)this->w2());
      printf(" [%f %f %f %f]\n",   (float)this->x3(), (float)this->y3(), (float)this->z3(), (float)this->w3());
      printf(" [%f %f %f %f]\n\n", (float)this->x4(), (float)this->y4(), (float)this->z4(), (float)this->w4());
    }
  };
}