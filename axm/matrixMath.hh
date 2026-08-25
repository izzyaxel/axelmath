#pragma once

#include "aliases.hh"
#include "types/mat4x4s.hh"

namespace axm
{
  /// Convert a quaternion to a 4x4 matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto quatToMat4x4(const quat<T>& rotation) -> mat4x4<T>
  {
    const T sqx = rotation.x() * rotation.x();
    const T sqy = rotation.y() * rotation.y();
    const T sqz = rotation.z() * rotation.z();
    const T sqw = rotation.w() * rotation.w();
    const T t1 = rotation.data[0] * rotation.y();
    const T t2 = rotation.data[2] * rotation.w();
    const T t3 = rotation.data[0] * rotation.z();
    const T t4 = rotation.data[1] * rotation.w();
    const T t5 = rotation.data[1] * rotation.z();
    const T t6 = rotation.data[0] * rotation.w();

    return
    {
      {sqx - sqy - sqz + sqw, (T)2 * (t1 + t2),       (T)2 * (t3 - t4),       (T)0},
      {(T)2 * (t1 - t2),      -sqx + sqy - sqz + sqw, (T)2 * (t5 + t6),       (T)0},
      {(T)2 * (t3 + t4),      (T)2 * (t5 - t6),       -sqx - sqy + sqz + sqw, (T)0},
      {(T)0,                  (T)0,                   (T)0,                   (T)1}
    };
  }

  /// Create a translation matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto translateMat(const vec3<T>& translate) -> mat4x4<T>
  {
    return
    {
      {(T)1,          (T)0,          (T)0,          (T)0},
      {(T)0,          (T)1,          (T)0,          (T)0},
      {(T)0,          (T)0,          (T)1,          (T)0},
      {translate.x(), translate.y(), translate.z(), (T)1}
    };
  }

  /// Create a rotation matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto rotateMat(const quat<T>& in) -> mat4x4<T>
  {
    return quatToMat4x4(in);
  }

  /// Create a scale matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto scaleMat(const vec3<T>& scale) -> mat4x4<T>
  {
    return
    {
      {scale.x(), (T)0,      (T)0,      (T)0},
      {(T)0,      scale.y(), (T)0,      (T)0},
      {(T)0,      (T)0,      scale.z(), (T)0},
      {(T)0,      (T)0,      (T)0,      (T)1}
    };
  }

  /// Create a scale matrix using 1 scale value
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto scaleMat(const T scalar) -> mat4x4<T>
  {
    return
    {
      {scalar,  (T)0,   (T)0,    (T)0},
      {(T)0,    scalar, (T)0,    (T)0},
      {(T)0,    (T)0,    scalar, (T)0},
      {(T)0,    (T)0,    (T)0,   (T)1}
    };
  }

  /// Create a model matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto modelMatrix(
    const vec3<T>& position,
    const quat<T>& rotation,
    const vec3<T>& scale) -> mat4x4<T>
  {
    const mat4x4 t = translateMat(position);
    const mat4x4 r = rotateMat(rotation);
    const mat4x4 s = scaleMat(scale);
    return t * r * s;
  }

  /// Create a model matrix with an offset
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto modelMatrix(
    const vec3<T>& position,
    const vec3<T>& origin,
    const quat<T>& rotation,
    const vec3<T>& scale) -> mat4x4<T>
  {
    const mat4x4<T> tOffset = translateMat(origin);
    const mat4x4<T> t = translateMat(position);
    const mat4x4<T> r = rotateMat(rotation);
    const mat4x4<T> s = scaleMat(scale);
    return t * r * s * tOffset;
  }

  /// Create a view matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto viewMatrix(
    const quat<T>& cameraRotation,
    const vec3<T>& cameraPosition) -> mat4x4<T>
  {
    const mat4x4<T> rotation = quatToMat4x4(cameraRotation.inverse());
    const mat4x4<T> translation = translateMat(cameraPosition.inverse());
    return translation * rotation;
  }

  /// Create a projection matrix that transforms positions according to perspective
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto perspectiveProjectionMatrix(
    const T fov,
    const T nearPlane,
    const T farPlane,
    const u32 width,
    const u32 height) -> mat4x4<T>
  {
    const T a = width / height;
    return
    {
      {(T)1 / (a * std::tan(fov / (T)2)),    (T)0,                          (T)0,                                                      (T)0},
      {(T)0,                                 (T)1 / (std::tan(fov / (T)2)), (T)0,                                                      (T)0},
      {(T)0,                                 (T)0,                          -((farPlane + nearPlane) / (farPlane - nearPlane)),        (T)-1},
      {(T)0,                                 (T)0,                          -(((T)2 * farPlane * nearPlane) / (farPlane - nearPlane)), (T)0},
    };
  }

  /// Create a projection matrix that transforms positions with no perspective
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto orthoProjectionMatrix(
    const T left,
    const T right,
    const T top,
    const T bottom,
    const T zNear,
    const T zFar) -> mat4x4<T>
  {
    return
    {
      {(T)2 / (right - left),              (T)0,                               (T)0,                               (T)0},
      {(T)0,                               (T)2 / (top - bottom),              (T)0,                               (T)0},
      {(T)0,                               (T)0,                               -((T)2 / (zFar - zNear)),           (T)0},
      {-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((zFar + zNear) / (zFar - zNear)), (T)1},
    };
  }

  /// Create a model-view-projection matrix to transform local coordinates to world coordinates
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto modelViewProjectionMatrix(
    const mat4x4<T>& model,
    const mat4x4<T>& view,
    const mat4x4<T>& projection) -> mat4x4<T>
  {
    return projection * view * model;
  }
}
