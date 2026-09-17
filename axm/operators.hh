#pragma once

#include "types/vec4s.hh"
#include "types/quaternions.hh"
#include "types/mat3x3s.hh"
#include "types/mat4x4s.hh"

//TODO add mixed mat3x3 and mat4x4 operators to auto convert up to mat4x4

namespace axm
{

  //==Vec2==============================================================================================================

  template <typename T>
  auto vec2<T>::operator = (const vec2& other) -> vec2&
  {
    if(other != *this)
    {
      this->data = other.data;
    }

    return *this;
  }

  template <typename T>
  auto vec2<T>::operator = (vec2&& other) noexcept -> vec2&
  {
    if(other != *this)
    {
      this->data = other.data;
      other.data = {};
    }

    return *this;
  }

  template <typename T>
  auto vec2<T>::operator [] (const size_t index) -> T&
  {
    size_t sanitized = index;
    if(sanitized > vec2::MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }
    return this->data[sanitized];
  }

  template <typename T>
  auto vec2<T>::operator [] (const size_t index) const -> const T&
  {
    size_t sanitized = index;
    if(sanitized > MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }
    return this->data[sanitized];
  }

  template <typename T>
  auto vec2<T>::operator - () const -> vec2 requires(IsNumeric<T>)
  {
    vec2 out{-this->x(), -this->y()};
    return out;
  }

  template <typename T>
  auto vec2<T>::operator + (const vec2& other) const -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() + other.x(), this->y() + other.y()};
  }

  template <typename T>
  auto vec2<T>::operator - (const vec2& other) const -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() - other.x(), this->y() - other.y()};
  }

  template <typename T>
  auto vec2<T>::operator * (const vec2& other) const -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() * other.x(), this->y() * other.y()};
  }

  template <typename T>
  auto vec2<T>::operator / (const vec2& other) const -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() / other.x(), this->y() / other.y()};
  }

  template <typename T>
  auto vec2<T>::operator += (const vec2& other) -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() + other.x(), this->y() + other.y()};
  }

  template <typename T>
  auto vec2<T>::operator -= (const vec2& other) -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() - other.x(), this->y() - other.y()};
  }

  template <typename T>
  auto vec2<T>::operator *= (const vec2& other) -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() * other.x(), this->y() * other.y()};
  }

  template <typename T>
  auto vec2<T>::operator /= (const vec2& other) -> vec2 requires(IsNumeric<T>)
  {
    return {this->x() / other.x(), this->y() / other.y()};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator + (const U other) const -> vec2
  {
    return {(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator - (const U other) const -> vec2
  {
    return {(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator * (const U other) const -> vec2
  {
    return {(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator / (const U other) const -> vec2
  {
    return {(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator += (const U other) -> vec2
  {
    return {this->x() + (T)other.x(), this->y() + (T)other.y()};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator -= (const U other) -> vec2
  {
    return {this->x() - (T)other.x(), this->y() - (T)other.y()};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator *= (const U other) -> vec2
  {
    return {this->x() * (T)other.x(), this->y() * (T)other.y()};
  }

  template <typename T>
  template <typename U>
  auto vec2<T>::operator /= (const U other) -> vec2
  {
    return {this->x() / (T)other.x(), this->y() / (T)other.y()};
  }

  template <typename T>
  auto vec2<T>::operator == (const vec2& other) const -> bool requires(HasEquivalenceOperator<T>)
  {
    return this->x() == other.x() && this->y() == other.y();
  }

  template <typename T>
  auto vec2<T>::operator < (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
  {
    return this->x() < other.x() && this->y() < other.y();
  }

  template <typename T>
  auto vec2<T>::operator > (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
  {
    return this->x() > other.x() && this->y() > other.y();
  }

  template <typename T>
  auto vec2<T>::operator <= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
  {
    return this->x() <= other.x() && this->y() <= other.y();
  }

  template <typename T>
  auto vec2<T>::operator >= (const vec2& other) const -> bool requires(HasComparisonOperators<T>)
  {
    return this->x() >= other.x() && this->y() >= other.y();
  }

  //==Vec3==============================================================================================================

  template <typename T>
  auto vec3<T>::operator = (const vec3& other) -> vec3&
  {
    if(this != &other)
    {
      this->data = other.data;
    }

    return *this;
  }

  template <typename T>
  auto vec3<T>::operator - () const -> vec3 requires(IsNumeric<T>)
  {
    vec3 out;
    out.x() = -this->x();
    out.y() = -this->y();
    out.z() = -this->z();
    return out;
  }

  template <typename T>
  auto vec3<T>::operator = (vec3&& other) noexcept -> vec3&
  {
    if(this != &other)
    {
      this->data = other.data;
      other.data = {};
    }

    return *this;
  }

  template <typename T>
  auto vec3<T>::operator [] (const size_t index) -> T&
  {
    size_t sanitized = index;
    if(sanitized > MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }
    return this->data.at(sanitized);
  }

  template <typename T>
  auto vec3<T>::operator [] (const size_t index) const -> const T&
  {
    size_t sanitized = index;
    if(sanitized > MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }
    return this->data.at(sanitized);
  }

  template <typename T>
  auto vec3<T>::operator == (const vec3& other) const -> bool requires(HasEquivalenceOperator<T>)
  {
    return this->x() == other.x() && this->y() == other.y() && this->z() == other.z();
  }

  template <typename T>
  auto vec3<T>::operator + (const vec3<T>& other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{this->x() + other.x(), this->y() + other.y(), this->z() + other.z()};
  }

  template <typename T>
  auto vec3<T>::operator - (const vec3<T>& other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{this->x() - other.x(), this->y() - other.y(), this->z() - other.z()};
  }

  template <typename T>
  auto vec3<T>::operator * (const vec3<T>& other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{this->x() * other.x(), this->y() * other.y(), this->z() * other.z()};
  }

  template <typename T>
  auto vec3<T>::operator / (const vec3<T>& other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{this->x() / other.x(), this->y() / other.y(), this->z() / other.z()};
  }

  template <typename T>
  auto vec3<T>::operator * (const quat<T>& other) const -> vec3 requires(IsNumeric<T>)
  {
    const quat q = normalize(other);
    const vec3 u = {q.x(), q.y(), q.z()};
    const vec3 uv = cross(u, *this);
    const vec3 uuv = cross(u, uv);
    const T dW = q.w() * (T)2;
    return *this + vec3{dW} * uv + vec3{(T)2} * uuv;
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator + (const U other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other), (T)((float)this->z() + (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator - (const U other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other), (T)((float)this->z() - (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator * (const U other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other), (T)((float)this->z() * (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator / (const U other) const -> vec3 requires(IsNumeric<T>)
  {
    return vec3{(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other), (T)((float)this->z() / (float)other)};
  }

  template <typename T>
  auto vec3<T>::operator += (const vec3& other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() += other.x();
    this->y() += other.y();
    this->z() += other.z();
    return *this;
  }

  template <typename T>
  auto vec3<T>::operator -= (const vec3& other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() -= other.x();
    this->y() -= other.y();
    this->z() -= other.z();
    return *this;
  }

  template <typename T>
  auto vec3<T>::operator *= (const vec3& other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() *= other.x();
    this->y() *= other.y();
    this->z() *= other.z();
    return *this;
  }

  template <typename T>
  auto vec3<T>::operator /= (const vec3& other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() /= other.x();
    this->y() /= other.y();
    this->z() /= other.z();
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator += (const U other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() = (T)((float)this->x() + (float)other);
    this->y() = (T)((float)this->y() + (float)other);
    this->z() = (T)((float)this->z() + (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator -= (const U other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() = (T)((float)this->x() - (float)other);
    this->y() = (T)((float)this->y() - (float)other);
    this->z() = (T)((float)this->z() - (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator *= (const U other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() = (T)((float)this->x() * (float)other);
    this->y() = (T)((float)this->y() * (float)other);
    this->z() = (T)((float)this->z() * (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec3<T>::operator /= (const U other) -> vec3& requires(IsNumeric<T>)
  {
    this->x() = (T)((float)this->x() / (float)other);
    this->y() = (T)((float)this->y() / (float)other);
    this->z() = (T)((float)this->z() / (float)other);
    return *this;
  }

  //==Vec4==============================================================================================================

  template <typename T>
  auto vec4<T>::operator = (const vec4& other) -> vec4&
  {
    if(other != *this)
    {
      this->data = other.data;
    }

    return *this;
  }

  template <typename T>
  auto vec4<T>::operator = (vec4&& other) noexcept -> vec4&
  {
    if(other != *this)
    {
      this->data = other.data;
      other.data = {};
    }

    return *this;
  }

  template <typename T>
  auto vec4<T>::operator - () const -> vec4 requires(MathStorageType<T>)
  {
    vec4 out;
    out.x() = -this->x();
    out.y() = -this->y();
    out.z() = -this->z();
    out.w() = -this->w();
    return out;
  }

  template <typename T>
  auto vec4<T>::operator = (const vec3<T>& other) -> vec4&
  {
    this->x() = other.x();
    this->y() = other.y();
    this->z() = other.z();
    return *this;
  }

  template <typename T>
  auto vec4<T>::operator [] (const size_t index) -> T&
  {
    size_t sanitized = index;
    if(sanitized > MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }

    return this->data[sanitized];
  }

  template <typename T>
  auto vec4<T>::operator [] (const size_t index) const -> const T&
  {
    size_t sanitized = index;
    if(sanitized > MAX_INDEX)
    {
      sanitized = MAX_INDEX;
    }

    return this->data[sanitized];
  }

  template <typename T>
  auto vec4<T>::operator + (const vec4& other) const -> vec4 requires(MathStorageType<T>)
  {
    return {this->x() + other.x(), this->y() + other.y(), this->z() + other.z(), this->w() + other.w()};
  }

  template <typename T>
  auto vec4<T>::operator - (const vec4& other) const -> vec4 requires(MathStorageType<T>)
  {
    return {this->x() - other.x(), this->y() - other.y(), this->z() - other.z(), this->w() - other.w()};
  }

  template <typename T>
  auto vec4<T>::operator * (const vec4& other) const -> vec4 requires(MathStorageType<T>)
  {
    return {this->x() * other.x(), this->y() * other.y(), this->z() * other.z(), this->w() * other.w()};
  }

  template <typename T>
  auto vec4<T>::operator / (const vec4& other) const -> vec4 requires(MathStorageType<T>)
  {
    return {this->x() / other.x(), this->y() / other.y(), this->z() / other.z(), this->w() / other.w()};
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator + (const U other) const -> vec4 requires(MathStorageType<T>)
  {
    return {(T)((float)this->x() + (float)other), (T)((float)this->y() + (float)other), (T)((float)this->z() + (float)other), (T)((float)this->w() + (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator - (const U other) const -> vec4 requires(MathStorageType<T>)
  {
    return {(T)((float)this->x() - (float)other), (T)((float)this->y() - (float)other), (T)((float)this->z() - (float)other), (T)((float)this->w() - (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator * (const U other) const -> vec4 requires(MathStorageType<T>)
  {
    return {(T)((float)this->x() * (float)other), (T)((float)this->y() * (float)other), (T)((float)this->z() * (float)other), (T)((float)this->w() * (float)other)};
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator / (const U other) const -> vec4 requires(MathStorageType<T>)
  {
    return {(T)((float)this->x() / (float)other), (T)((float)this->y() / (float)other), (T)((float)this->z() / (float)other), (T)((float)this->w() / (float)other)};
  }

  template <typename T>
  auto vec4<T>::operator += (const vec4& other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() += other.x();
    this->y() += other.y();
    this->z() += other.z();
    this->w() += other.w();
    return *this;
  }

  template <typename T>
  auto vec4<T>::operator -= (const vec4& other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() -= other.x();
    this->y() -= other.y();
    this->z() -= other.z();
    this->w() -= other.w();
    return *this;
  }

  template <typename T>
  auto vec4<T>::operator *= (const vec4& other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() *= other.x();
    this->y() *= other.y();
    this->z() *= other.z();
    this->w() *= other.w();
    return *this;
  }

  template <typename T>
  auto vec4<T>::operator /= (const vec4& other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() /= other.x();
    this->y() /= other.y();
    this->z() /= other.z();
    this->w() /= other.w();
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator += (const U other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() = (T)((float)this->x() + (float)other);
    this->y() = (T)((float)this->y() + (float)other);
    this->z() = (T)((float)this->z() + (float)other);
    this->w() = (T)((float)this->w() + (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator -= (const U other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() = (T)((float)this->x() - (float)other);
    this->y() = (T)((float)this->y() - (float)other);
    this->z() = (T)((float)this->z() - (float)other);
    this->w() = (T)((float)this->w() - (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator *= (const U other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() = (T)((float)this->x() * (float)other);
    this->y() = (T)((float)this->y() * (float)other);
    this->z() = (T)((float)this->z() * (float)other);
    this->w() = (T)((float)this->w() * (float)other);
    return *this;
  }

  template <typename T>
  template <typename U>
  auto vec4<T>::operator /= (const U other) -> vec4& requires(MathStorageType<T>)
  {
    this->x() = (T)((float)this->x() / (float)other);
    this->y() = (T)((float)this->y() / (float)other);
    this->z() = (T)((float)this->z() / (float)other);
    this->w() = (T)((float)this->w() / (float)other);
    return *this;
  }

  template <typename T>
  auto vec4<T>::operator == (const vec4& other) const -> bool requires(HasEquivalenceOperator<T>)
  {
    return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
  }

  //==Quaternion========================================================================================================

  template <MathStorageType T>
  auto quat<T>::operator = (const quat& other) -> quat&
  {
    if(this != &other)
    {
      this->data = other.data;
    }
    return *this;
  }

  template <MathStorageType T>
  auto quat<T>::operator = (quat&& other) noexcept -> quat&
  {
    if(this != &other)
    {
      this->data = other.data;
      other.data = {};
    }
    return *this;
  }

  template <MathStorageType T>
  auto quat<T>::operator [] (size_t index) -> T&
  {
    if(index > 3)
    {
      return {};
    }

    return this->data[index];
  }

  template <MathStorageType T>
  auto quat<T>::operator [] (size_t index) const -> T
  {
    if(index > 3)
    {
      return {};
    }

    return this->data[index];
  }

  template <MathStorageType T>
  auto quat<T>::operator == (const quat& other) const -> bool requires(HasEquivalenceOperator<T>)
  {
    return this->x() == other.x() && this->y() == other.y() && this->z() == other.z() && this->w() == other.w();
  }

  template <MathStorageType T>
  auto quat<T>::operator += (const quat& other) -> quat requires(IsNumeric<T>)
  {
    this->x() += other.x();
    this->y() += other.y();
    this->z() += other.z();
    this->w() += other.w();
    return *this;
  }

  template <MathStorageType T>
  auto quat<T>::operator *= (const float val) -> quat requires(IsNumeric<T>)
  {
    this->x() *= val;
    this->y() *= val;
    this->z() *= val;
    this->w() *= val;
    return *this;
  }

  template <MathStorageType T>
  auto quat<T>::operator *= (const quat& other) -> quat requires(IsNumeric<T>)
  {
    this->x() = this->x() * other.w() + this->w() * other.x() + this->y() * other.z() - this->z() * other.y();
    this->y() = this->y() * other.w() + this->w() * other.y() + this->z() * other.x() - this->x() * other.z();
    this->z() = this->z() * other.w() + this->w() * other.z() + this->x() * other.y() - this->y() * other.x();
    this->w() = this->w() * other.w() - this->x() * other.x() - this->y() * other.y() - this->z() * other.z();
    return *this;
  }

  template <MathStorageType T>
  auto quat<T>::operator + (const quat& other) const -> quat requires(IsNumeric<T>)
  {
    return quat
    {
      this->x() + other.x(),
      this->y() + other.y(),
      this->z() + other.z(),
      this->w() + other.w()};
  }

  template <MathStorageType T>
  auto quat<T>::operator * (const float val) const -> quat requires(IsNumeric<T>)
  {
    return quat
    {
      this->x() * val,
      this->y() * val,
      this->z() * val,
      this->w() * val
    };
  }

  template <MathStorageType T>
  auto quat<T>::operator * (const quat& other) const -> quat requires(IsNumeric<T>)
  {
    return quat
    {
      this->x() * other.w() + this->w() * other.x() + this->y() * other.z() - this->z() * other.y(),
      this->y() * other.w() + this->w() * other.y() + this->z() * other.x() - this->x() * other.z(),
      this->z() * other.w() + this->w() * other.z() + this->x() * other.y() - this->y() * other.x(),
      this->w() * other.w() - this->x() * other.x() - this->y() * other.y() - this->z() * other.z()
   };
  }

  template <MathStorageType T>
  auto quat<T>::operator * (const vec3<T>& other) const -> vec3<T> requires(IsNumeric<T>)
  {
    const quat q = normalize(*this);
    const vec3 u = {q.x(), q.y(), q.z()};
    const vec3 uv = cross(u, other);
    const vec3 uuv = cross(u, uv);
    const T dW = q.w() * (T)2;
    return other + vec3{dW} * uv + vec3<T>{2} * uuv;
  }

  //==Mat3x3============================================================================================================

  template <MathStorageType T>
  auto mat3x3<T>::operator == (const mat3x3& other) const -> bool requires(HasEquivalenceOperator<T>)
  {
    return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2];
  }

  template <MathStorageType T>
  auto mat3x3<T>::operator [] (const size_t index) const -> vec3<T>
  {
    if(index > 2)
    {
      return {};
    }

    return this->data[index];
  }

  template <MathStorageType T>
  auto mat3x3<T>::operator * (const T val) const -> mat3x3 requires(HasMathOperators<T>)
  {
    return
    {
      {this->x1() * val, this->y1() * val, this->z1() * val},
      {this->x2() * val, this->y2() * val, this->z2() * val},
      {this->x3() * val, this->y3() * val, this->z3() * val}
    };
  }

  template <MathStorageType T>
  auto mat3x3<T>::operator * (const mat3x3& other) const -> mat3x3 requires(HasMathOperators<T>)
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

  //==Mat4x4============================================================================================================

  template <MathStorageType T>
  auto mat4x4<T>::operator == (const mat4x4& other) const -> bool
  {
    return this->data[0] == other.data[0] && this->data[1] == other.data[1] && this->data[2] == other.data[2] && this->data[3] == other.data[3];
  }

  template <MathStorageType T>
  auto mat4x4<T>::operator [] (const size_t index) const -> vec4<T>
  {
    if(index > 3)
    {
      return {};
    }

    return this->data[index];
  }

  template <MathStorageType T>
  auto mat4x4<T>::operator * (const T val) const -> mat4x4 requires(MathStorageType<T>)
  {
    return
    {
      {this->x1() * val, this->y1() * val, this->z1() * val, this->w1() * val},
      {this->x2() * val, this->y2() * val, this->z2() * val, this->w2() * val},
      {this->x3() * val, this->y3() * val, this->z3() * val, this->w3() * val},
      {this->x4() * val, this->y4() * val, this->z4() * val, this->w4() * val}
    };
  }

  template <MathStorageType T>
  auto mat4x4<T>::operator * (const mat4x4& other) const -> mat4x4 requires(MathStorageType<T>)
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

  template <MathStorageType T>
  auto mat4x4<T>::operator * (const vec4<T>& vec) const -> vec4<T> requires(MathStorageType<T>)
  {
    return
    {
      vec.x() * this->x1() + vec.y() * this->y1() + vec.z() * this->z1() + vec.w() * this->w1(),
      vec.x() * this->x2() + vec.y() * this->y2() + vec.z() * this->z2() + vec.w() * this->w2(),
      vec.x() * this->x3() + vec.y() * this->y3() + vec.z() * this->z3() + vec.w() * this->w3(),
      vec.x() * this->x4() + vec.y() * this->y4() + vec.z() * this->z4() + vec.w() * this->w4(),
    };
  }

}
