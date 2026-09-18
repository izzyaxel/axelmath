#pragma once

#ifndef AXM_INTERPOLATION_GUARD
#define AXM_INTERPOLATION_GUARD

#include "math.hh"
#include "types/quaternions.hh"
#include "types/vec4s.hh"

#include <numbers>

namespace axm
{

  /// Adjustable lerp
  /// \param a Start
  /// \param b End
  /// \param progress 0-1
  /// \param curve ==1 is linear, >1 is ease in-out, <1 is inverse ease in-out
  template <typename T>
  [[nodiscard]] T alerp(const T a, const T b, const T progress, const T curve)
  {
    T expProg = std::pow(progress, curve);
    T lerp = expProg / (expProg + std::pow((T)1 - progress, curve));
    return ((T)1 - lerp) * a + lerp * b;
  }

  /// Logarithmic lerp, return value approaches b logarithmically faster as progress approaches 1
  /// \param a Start
  /// \param b End
  /// \param progress 0-1
  template <typename T>
  [[nodiscard]] T loglerp(const T a, const T b, const T progress)
  {
    return a * std::pow(b / a, progress);
  }

  /// Framerate independent linear interpolation
  /// \param current Start point, this will be updated with the interpolated value
  /// \param to End point
  /// \param decay Exponential decay value, hold constant for each 'current' (useful range: 1 - 25)
  /// \param deltaTime Time since the last frame occurred
  template <typename T, typename U, typename V>
  void integraldeltalerp(T& current, const T to, const U decay, const V deltaTime)
  {
    current = to + (current - to) * std::exp(-decay * deltaTime);
  }

  /// Standard linear interpolation
  /// \param a Start
  /// \param b End
  /// \param progress 0-1
  template <typename T>
  [[nodiscard]] T lerp(const T a, const T b, const T progress)
  {
    return a + (b - a) * progress;
  }

  //Vec2
  /// Lerp between 2 2-dimensional vectors
  template <typename T>
  [[nodiscard]] vec2<T> lerp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    vec2<T> out;
    out.x() = lerp(src.x(), dest.x(), progress);
    out.y() = lerp(src.y(), dest.y(), progress);
    return out;
  }

  /// Ease out lerp: fast in slow out
  template <typename T>
  [[nodiscard]] vec2<T> eoerp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec2<T> eierp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec2<T> exeoerp(const vec2<T>& src, const vec2<T>& dest, float progress)
  {
    return lerp(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp: slower in fast out
  template <typename T> [[nodiscard]] vec2<T> exeierp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T> [[nodiscard]] vec2<T> serp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T> [[nodiscard]] vec2<T> sserp(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }


  //Vec3
  /// Lerp between 2 3-dimensional vectors
  template <typename T>
  [[nodiscard]] vec3<T> lerp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    vec3<T> out;
    out[0] = progress * dest[0] + ((T)1.0 - progress) * src[0];
    out[1] = progress * dest[1] + ((T)1.0 - progress) * src[1];
    out[2] = progress * dest[2] + ((T)1.0 - progress) * src[2];
    return out;
  }

  /// Ease out lerp: fast in slow out
  template <typename T>
  [[nodiscard]] vec3<T> eoerp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec3<T> eierp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec3<T> exeoerp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp slower in fast out
  template <typename T>
  [[nodiscard]] vec3<T> exeierp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T>
  [[nodiscard]] vec3<T> serp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T>
  [[nodiscard]] vec3<T> sserp(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }

  /// Lerp between 2 4-dimensional vectors
  template <typename T>
  [[nodiscard]] vec4<T> lerp(const vec4<T>& src, const vec4<T>& dest, float progress)
  {
    vec4<T> out;
    out[0] = progress * dest[0] + (1 - progress) * src[0];
    out[1] = progress * dest[1] + (1 - progress) * src[1];
    out[2] = progress * dest[2] + (1 - progress) * src[2];
    out[3] = progress * dest[3] + (1 - progress) * src[3];
    return out;
  }

  /// Ease out lerp: fast in slow out
  template <typename T>
  [[nodiscard]] vec4<T> eoerp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec4<T> eierp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec4<T> exeoerp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp: slower in fast out
  template <typename T>
  [[nodiscard]] vec4<T> exeierp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T>
  [[nodiscard]] vec4<T> serp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T>
  [[nodiscard]] vec4<T> sserp(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerp(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lerp(const quat<T>& a, const quat<T>& b, const T t) -> quat<T>
  {
    return quat<T>{a * (1.0f - t) + b * t};
  }

  /// Quaternion spherical linear interpolation
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto slerp(const quat<T>& a, const quat<T>& b, const T t) -> quat<T>
  {
    quat<T> aNorm = normalize(a);
    quat<T> bNorm = normalize(b);
    float dotProd = dot(aNorm, bNorm);
    quat<T> qB = aNorm;

    if(dotProd < 0.0f)
    {
      qB.x() = -bNorm.x();
      qB.y() = -bNorm.y();
      qB.z() = -bNorm.z();
      qB.w() = -bNorm.w();
      dotProd = -dotProd;
    }

    if(dotProd > 0.9995f)
    {
      return normalize(lerp(a, qB, t));
    }

    float theta = std::acos(dotProd);
    const float sinTheta = std::sin(theta);
    float invSinTheta = 1.0f / sinTheta;

    const float scaleA = std::sin((1.0f - t) * theta) * invSinTheta;
    const float scaleB = std::sin(t * theta) * invSinTheta;

    return a * scaleA + b * scaleB;
  }
}

#endif
