#pragma once

#include "aliases.hh"
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
  [[nodiscard]] vec2<T> lerpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    vec2<T> out;
    out.x() = lerp(src.x(), dest.x(), progress);
    out.y() = lerp(src.y(), dest.y(), progress);
    return out;
  }

  /// Ease out lerp: fast in slow out
  template <typename T>
  [[nodiscard]] vec2<T> eoerpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerpV2(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec2<T> eierpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerpV2(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec2<T> exeoerpV2(const vec2<T>& src, const vec2<T>& dest, float progress)
  {
    return lerpV2(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp: slower in fast out
  template <typename T> [[nodiscard]] vec2<T> exeierpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerpV2(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T> [[nodiscard]] vec2<T> serpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerpV2(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T> [[nodiscard]] vec2<T> sserpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
  {
    return lerpV2(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }


  //Vec3
  /// Lerp between 2 3-dimensional vectors
  template <typename T>
  [[nodiscard]] vec3<T> lerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    vec3<T> out;
    out[0] = progress * dest[0] + ((T)1.0 - progress) * src[0];
    out[1] = progress * dest[1] + ((T)1.0 - progress) * src[1];
    out[2] = progress * dest[2] + ((T)1.0 - progress) * src[2];
    return out;
  }

  /// Ease out lerp: fast in slow out
  template <typename T>
  [[nodiscard]] vec3<T> eoerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec3<T> eierpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec3<T> exeoerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp slower in fast out
  template <typename T>
  [[nodiscard]] vec3<T> exeierpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T>
  [[nodiscard]] vec3<T> serpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T>
  [[nodiscard]] vec3<T> sserpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
  {
    return lerpV3(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }

  /// Lerp between 2 4-dimensional vectors
  template <typename T>
  [[nodiscard]] vec4<T> lerpV4(const vec4<T>& src, const vec4<T>& dest, float progress)
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
  [[nodiscard]] vec4<T> eoerpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)(std::sin(progress * std::numbers::pi * (T)0.5)));
  }

  /// Ease in lerp: slow in fast out
  template <typename T>
  [[nodiscard]] vec4<T> eierpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)((T)1.0 - std::cos(progress * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease out lerp: fast in slower out
  template <typename T>
  [[nodiscard]] vec4<T> exeoerpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)(std::sin((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Exponential ease in lerp: slower in fast out
  template <typename T>
  [[nodiscard]] vec4<T> exeierpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)((T)1.0 - std::cos((progress * progress) * std::numbers::pi * (T)0.5)));
  }

  /// Smoothstep lerp: slow in slow out
  template <typename T>
  [[nodiscard]] vec4<T> serpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
  }

  /// Smootherstep lerp: slower in slower out
  template <typename T>
  [[nodiscard]] vec4<T> sserpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
  {
    return lerpV4(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lerpQuat(const quat<T>& a, const quat<T>& b, const T t) -> quat<T>
  {
    return quat<T>{a * (1.0f - t) + b * t};
  }

  /// Quaternion spherical linear interpolation
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto slerpQuat(const quat<T>& a, const quat<T>& b, const T t) -> quat<T>
  {
    quat<T> aNorm = a.normalized();
    quat<T> bNorm = b.normalized();
    float dot = aNorm.dot(bNorm);
    quat<T> qB = aNorm;

    if(dot < 0.0f)
    {
      qB.x() = -bNorm.x();
      qB.y() = -bNorm.y();
      qB.z() = -bNorm.z();
      qB.w() = -bNorm.w();
      dot = -dot;
    }

    if(dot > 0.9995f)
    {
      return lerpQuat(a, qB, t).normalized();
    }

    float theta = std::acos(dot);
    const float sinTheta = std::sin(theta);
    float invSinTheta = 1.0f / sinTheta;

    const float scaleA = std::sin((1.0f - t) * theta) * invSinTheta;
    const float scaleB = std::sin(t * theta) * invSinTheta;

    return a * scaleA + b * scaleB;
  }
}
