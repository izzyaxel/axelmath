#pragma once

#include "../concepts.hh"
#include "../types/vec3s.hh"

namespace axm
{

  template <MathStorageType T>
  struct quat;

  /// A 3x3 matrix
  /// Immutable
  /// Column-dominant by default, but can be transposed into row-dominant
  /// @tparam T Any type or class supporting the == (equivalence) operator and all basic math operators (+ - * /), plain numeric types will cause the matrix to be initialized to identity
  template<MathStorageType T>
  struct mat3x3
  {
    const vec3<vec3<T>> data;

    mat3x3() requires(!IsNumeric<T>) = default;

    /// When using a mat4x4 with numeric values, we want to set the matrix to identity
    mat3x3() requires(IsNumeric<T>) : data({1, 0, 0},
                                           {0, 1, 0},
                                           {0, 0, 1}) {}

    mat3x3(const mat3x3& other) : data(other.data) {}

    mat3x3(mat3x3&& other) noexcept = default;

    auto operator = (const mat3x3& other) -> mat3x3&
    {
      if(*this != other)
      {
        this->~mat3x3();
        ::new(this)mat3x3(other);
      }
      return *this;
    }

    auto operator = (mat3x3&& other) noexcept -> mat3x3&
    {
      if(*this != other)
      {
        this->~mat3x3();
        ::new(this)mat3x3(other);
        other.~mat3x3();
      }
      return *this;
    }

    mat3x3(
      const T valx1, const T valy1, const T valz1, //Column 0
      const T valx2, const T valy2, const T valz2, //Column 1
      const T valx3, const T valy3, const T valz3  //Column 2
      ) : data({valx1, valy1, valz1},
               {valx2, valy2, valz2},
               {valx3, valy3, valz3}) {}

    mat3x3(const vec3<T>& column0, const vec3<T>& column1, const vec3<T>& column2) : data(column0, column1, column2) {}

    auto operator == (const mat3x3& other) const -> bool
    {
      return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2];
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator [] (const size_t index) const -> vec3<T>
    {
      if(index > 2)
      {
        return {};
      }

      return this->data[index];
    }

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
    auto operator * (const T val) const -> mat3x3
    {
      return
      {
        {this->x1() * val, this->y1() * val, this->z1() * val},
        {this->x2() * val, this->y2() * val, this->z2() * val},
        {this->x3() * val, this->y3() * val, this->z3() * val}
      };
    }

    CONST USE_RESULT CANNOT_FAIL
    auto operator * (const mat3x3 other) const -> mat3x3
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

    //TODO how to invert a 3x3
    /*CONST USE_RESULT CANNOT_FAIL
    auto inverse() const -> mat3x3
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
    }*/

    CONST USE_RESULT CANNOT_FAIL
    auto transposed() const -> mat3x3
    {
      return
      {
        {this->x1(), this->x2(), this->x3()},
        {this->y1(), this->y2(), this->y3()},
        {this->z1(), this->z2(), this->z3()},
      };
    }

    auto print(const std::string& msg) const -> void
    {
      printf("mat3x3: %s\n", msg.c_str());
      printf(" [%f %f %f]\n",   (float)this->x1(), (float)this->y1(), (float)this->z1());
      printf(" [%f %f %f]\n",   (float)this->x2(), (float)this->y2(), (float)this->z2());
      printf(" [%f %f %f]\n",   (float)this->x3(), (float)this->y3(), (float)this->z3());
    }
  };
}
