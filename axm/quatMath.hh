#pragma once

#include "types/quaternions.hh"

namespace axm
{
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mat4x4ToQuat(const mat4x4<T>& in) -> quat<T>
  {
    T trace = in[0][0] + in[1][1] + in[2][2];
    if(trace > 0)
    {
      T root = (T)2 * std::sqrt(trace + (T)1);
      return
      {
        (in[2][1] - in[1][2]) / root,
        (in[0][2] - in[2][0]) / root,
        (in[1][0] - in[0][1]) / root,
        root / (T)4
      };
    }

    if(in[0][0] > in[1][1] && in[0][0] > in[2][2])
    {
      T root = (T)2 * std::sqrt((T)1 + in[0][0] - in[1][1] - in[2][2]);
      return
      {
        root / (T)4,
        (in[0][1] + in[1][0]) / root,
        (in[0][2] + in[2][0]) / root,
        (in[2][1] - in[1][2]) / root
      };
    }

    if(in[1][1] > in[2][2])
    {
      T root = (T)2 * std::sqrt((T)1 + in[1][1] - in[0][0] - in[2][2]);
      return
      {
        (in[0][1] + in[1][0]) / root,
        root / (T)4,
        (in[1][2] + in[2][1]) / root,
        (in[0][2] - in[2][0]) / root
      };
    }

    T root = (T)2 * std::sqrt((T)1 + in[2][2] - in[0][0] - in[1][1]);
    return
    {
      (in[0][2] + in[2][0]) / root,
      (in[1][2] + in[2][1]) / root,
      root / (T)4,
      (in[1][0] - in[0][1]) / root
    };
  }

  /// Create a rotation quaternion to multiply an orientation quaternion by, using relative mouse movement values
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto rotationFromMouseMovement(
    const T xrel,
    const T yrel,
    const T lookSensitivity) -> quat<T>
  {
    float a = (-xrel * lookSensitivity) / 2.0f;
    quat<T> xQuat{0.0f, std::sin(a), 0.0f, std::cos(a)};
    a = (-yrel * lookSensitivity) / 2.0f;
    quat<T> yQuat(std::sin(a), 0.0f, 0.0f, std::cos(a));
    quat out = xQuat * yQuat;
    return out.normalized();
  }

  /// Convert euler angles ({roll, pitch, yaw} in radians) to a quaternion rotation
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  static auto fromEulerRotation(const vec3<T>& euler) -> quat<T>
  {
    constexpr float half = 0.5f;
    const T cYaw = std::cos(euler[2] * half);
    const T sYaw = std::sin(euler[2] * half);
    const T cRoll = std::cos(euler[0] * half);
    const T sRoll = std::sin(euler[0] * half);
    const T cPitch = std::cos(euler[1] * half);
    const T sPitch = std::sin(euler[1] * half);

    quat<T> out
    {
      cYaw * sRoll * cPitch - sYaw * cRoll * sPitch,
      cYaw * cRoll * sPitch + sYaw * sRoll * cPitch,
      sYaw * cRoll * cPitch - cYaw * sRoll * sPitch,
      cYaw * cRoll * cPitch + sYaw * sRoll * sPitch
    };

    return out.normalized();
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto fromAxialRotation(const vec4<T>& in) -> quat<T>
  {
    const float a = in[3] / (T)2;
    const float s = std::sin(a);

    const quat out
    {
      in[0] * s,
      in[1] * s,
      in[2] * s,
      std::cos(a)
    };

    return out.normalized();
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto fromAxialRotation(
    const T& xIn,
    const T& yIn,
    const T& zIn,
    const T& angle) -> quat<T>
  {
    const float a = angle / (T)2;
    const float s = std::sin(a);

    const quat out
    {
      xIn * s,
      yIn * s,
      zIn * s,
      std::cos(a)
    };

    return out.normalized();
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto fromAxialRotation(
    const vec3<T>& xyzIn,
    const T& angle) -> quat<T>
  {
    const float a = angle / (T)2;
    const float s = std::sin(a);

    const quat out
    {
      xyzIn[0] * s,
      xyzIn[1] * s,
      xyzIn[2] * s,
      std::cos(a)
    };

    return out.normalized();
  }

  /// Calculate a right handed quaternion rotation that aims at the given coordinates
  /// \param originPos Typically the position of the camera, also called eye
  /// \param targetPos The point in the world to aim at
  /// \param upVec A normalized direction vector specifying what direction up is to be considered
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAtRH(
    const vec3<T>& originPos,
    const vec3<T>& targetPos,
    const vec3<T>& upVec) -> quat<T>
  {
    const vec3 forward = (originPos - targetPos).normalized();
    const vec3 right = upVec.cross(forward).normalized();
    const vec3 orthogonalUp = forward.cross(right).normalized();

    const mat4x4<T> comp
    {
      {right[0], orthogonalUp[0], forward[0], (T)0},
      {right[1], orthogonalUp[1], forward[1], (T)0},
      {right[2], orthogonalUp[2], forward[2], (T)0},
      {(T)0,     (T)0,            (T)0,       (T)0}
    };

    return mat4x4ToQuat(comp);
  }

  /// Calculate a left handed quaternion rotation that aims at the given coordinates
  /// \param originPos Typically the position of the camera, also called eye
  /// \param targetPos The point in the world to aim at
  /// \param upVec A normalized direction vector specifying what direction up is to be considered
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAtLH(
    const vec3<T>& originPos,
    const vec3<T>& targetPos,
    const vec3<T>& upVec) -> quat<T>
  {
    const vec3 forward = (targetPos - originPos).normalized();
    const vec3 left = forward.cross(-upVec).normalized();
    const vec3 orthogonalUp = forward.cross(left).normalized();

    const mat4x4<T> comp
    {
      {left[0], orthogonalUp[0], forward[0], (T)0},
      {left[1], orthogonalUp[1], forward[1], (T)0},
      {left[2], orthogonalUp[2], forward[2], (T)0},
      {(T)0,    (T)0,            (T)0,       (T)0}
    };

    return mat4x4ToQuat(comp);
  }

  /// A cumulative/SLERPed version of lookAt
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAt(
    const vec3<T> originPos,
    const vec3<T> targetPos,
    const quat<T>& currentRotation,
    const T lerp = (T)1) -> quat<T>
  {
    vec3 frontTo = vec3{targetPos - originPos}.normalized() * currentRotation.conjugated();
    return vecDelta({(T)0, (T)0, (T)1}, frontTo, lerp);
  }

  /// Is this a SLERP?
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto vecDelta(
      const vec3<T> from,
      const vec3<T> to,
      T lerp = (T)1) -> quat<T>
  {
    lerp = std::clamp(lerp, (T)0, (T)1);

    const T dot = std::clamp(to.dot(from), (T)-1, (T)1);
    if(dot == (T)1)
    {
      return quat{(T)0, (T)0, (T)0, (T)1};
    }
    if(dot == (T)-1)
    {
      return quat{(T)0, (T)0, (T)1, (T)0};
    }

    const T rot = std::acos(dot);
    const vec3<T> rotAxis = to.cross(from).normalized();
    return fromAxialRotation(rotAxis.x(), rotAxis.y(), rotAxis.z(), rot * lerp);
  }

  /// Prevent a quaternion rotation from exceeding a certain angle like you could do with euler angles
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto limitRotationRange(
    const quat<T> in,
    const vec3<T> up,
    const T angleLimit,
    const T lerp = (T)1) -> quat<T>
  {
    vec3<T> upQ = -up * in.conjugated();
    upQ.normalize();
    T dot = vec3<T>{(T)0, (T)1, (T)0}.dot(upQ);

    if(dot >= 1)
    {
      return {};
    }

    if(dot < -1)
    {
      dot = -1;
    }

    T angle = std::acos(dot);
    if(angle > angleLimit)
    {
      return {};
    }

    vec3<T> rotAxis = vec3<T>{(T)0, (T)1, (T)0}.cross(upQ);
    rotAxis.normalize();
    return fromAxialRotation(rotAxis.x(), rotAxis.y(), rotAxis.z(), (angleLimit - angle) * lerp);
  }

  ///Prevent rolling when moving the camera in circles by reorienting the quaternion with an up vector
  template <MathStorageType T>
 GNUCONST USE_RESULT CANNOT_FAIL
  auto correctOrientation(
    const quat<T>& in,
    const vec3<T>& up,
    T lerp = (T)1) -> quat<T>
  {
    vec3<T> upQ = up * in.conjugated();
    upQ.normalize();
    vec3<T> side = vec3<T>{(T)0, (T)0, (T)1}.cross(-upQ);
    side.normalize();

    if(vec3<T>{(T)0, (T)1, (T)0}.dot(upQ) <= 0)
    {
      side = -side;
    }

    vec3 upFixed = vec3{(T)0, (T)0, (T)1}.cross(side).normalized();
    return vecDelta({(T)0, (T)1, (T)0}, upFixed, lerp);
  }
}
