#pragma once

#include "types/vec4s.hh"
#include "types/quaternions.hh"
#include "types/mat3x3s.hh"
#include "types/mat4x4s.hh"

#include <numbers>
#include <algorithm>
#include <cmath>

//TODO add mixed mat3x3 and mat4x4 operations that auto convert up to mat4x4
//TODO mat3x3 math to optimize RAM usage when when mat4x4 isnt required?
namespace axm
{

  GNUCONST USE_RESULT CANNOT_FAIL
  inline auto closeEnough(const float val, const float target) -> bool
  {
    if(std::abs(val - target) <= 1e-6)
    {
      return true;
    }
    const float max = std::max(std::abs(val), std::abs(target));
    return std::abs(val - target) <= max * 1e-8f;
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto degToRad(const T degree) -> T
  {
    return degree * (std::numbers::pi / (T)180);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const T a, const T b) -> T
  {
    return std::abs(a - b);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const vec2<T>& a, const vec2<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2));
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto distSqr(const vec2<T>& a, const vec2<T>& b) -> T
  {
    return std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dist(const vec3<T>& a, const vec3<T>& b) -> T
  {
    return std::sqrtf(std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2) + std::powf(b.z() - a.z(), (T)2));
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto distSqr(const vec3<T>& a, const vec3<T>& b) -> T
  {
    return std::powf(b.x() - a.x(), (T)2) + std::powf(b.y() - a.y(), (T)2) + std::powf(b.z() - a.z(), (T)2);
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto sign(const T& val) -> i8
  {
    return val < 0 ? -1 : (val == 0 ? 0 : 1);
  }

  //==Vec2==============================================================================================================

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dot(const vec2<T>& in, const vec2<T>& other) -> T
  {
    return in.x() * other.x() + in.y() * other.y();
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mag(const vec2<T>& in) -> T
  {
    return std::sqrt(in.x() * in.x() + in.y * in.y());
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto normalize(const vec2<T>& in) -> vec2<T>
  {
    vec2<T> out = in;
    const T length = mag(in);
    if(length > (T)0)
    {
      out /= length;
    }

    return out;
  }

  //==Vec3==============================================================================================================

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto sqrt(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = (T)std::sqrt(in.x());
    out.y() = (T)std::sqrt(in.y());
    out.z() = (T)std::sqrt(in.z());
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto pow(const vec3<T>& in, const T val) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = (T)std::pow(in.x(), val);
    out.y() = (T)std::pow(in.y(), val);
    out.z() = (T)std::pow(in.z(), val);
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto pow(const vec3<T>& in, const vec3<T>& other) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = (T)std::pow(in.x(), other.x());
    out.y() = (T)std::pow(in.y(), other.y());
    out.z() = (T)std::pow(in.z(), other.z());
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto floor(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out{};
    out->x() = (T)std::floor(in.x());
    out->y() = (T)std::floor(in.y());
    out->z() = (T)std::floor(in.z());
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto ceil(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = (T)std::ceil(in.x());
    out.y() = (T)std::ceil(in.y());
    out.z() = (T)std::ceil(in.z());
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto round(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = (T)std::round(in.x());
    out.y() = (T)std::round(in.y());
    out.z() = (T)std::round(in.z());
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto invert(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = -in.x();
    out.y() = -in.y();
    out.z() = -in.z();
    return out;
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mag(const vec3<T>& in) -> T
  {
    return std::sqrt(in.x() * in.x() + in.y() * in.y() + in.z() * in.z());
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dot(const vec3<T>& in, const vec3<T>& other) -> T
  {
    return in.x() * other.x() + in.y() * other.y() + in.z() * other.z();
  }

  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto cross(const vec3<T>& in, const vec3<T>& other) -> vec3<T>
  {
    vec3<T> out{};
    out.x() = in.y() * other.z() - in.z() * other.y();
    out.y() = in.z() * other.x() - in.x() * other.z();
    out.z() = in.x() * other.y() - in.y() * other.x();
    return out;
  }

  template <typename T>
  CANNOT_FAIL
  auto normalize(const vec3<T>& in) -> vec3<T>
  {
    vec3<T> out = in;
    const T length = mag(in);
    if(length > (T)0)
    {
      out /= length;
    }

    return out;
  }

  //==Vec4==============================================================================================================

  template <IsNumeric T>
  USE_RESULT CANNOT_FAIL
  auto mag(const vec4<T>& in) -> T
  {
    return std::sqrt(in.x() * in.x() + in.y() * in.y() + in.z() * in.z() * in.w() * in.w());
  }

  template <IsNumeric T>
  USE_RESULT CANNOT_FAIL
  auto normalize(const vec4<T>& in) -> vec4<T>
  {
    vec4<T> out = in;
    const T length = mag(in);
    if(length > (T)0)
    {
      out /= length;
    }
    return out;
  }

  //==Quaternion========================================================================================================

  template <typename T>
  auto rotateVec3 (const quat<T>& rotation, const vec3<T>& vector) -> vec3<T> requires(IsNumeric<T>)
  {
    const quat<T> q = normalize(rotation);
    const vec3<T> u = {q.x(), q.y(), q.z()};
    const vec3<T> uv = cross(u, vector);
    const vec3<T> uuv = cross(u, uv);
    const T dW = q.w() * (T)2;
    return vector + vec3{dW} * uv + vec3{(T)2} * uuv;
  }

  ///
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto conjugate(const quat<T>& in) -> quat<T>
  {
    return quat{-in.x(), -in.y(), -in.z(), in.w()};
  }

  /// Get the magnitude(length) of a quaternion
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mag(const quat<T>& in) -> T
  {
    return std::sqrt(in.x() * in.x() + in.y() * in.y() + in.z() * in.z() + in.w() * in.w());
  }

  /// Make a unit length version of a quaternion
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto normalize(const quat<T>& in) -> quat<T>
  {
    T length = mag(in);
    if(closeEnough(length, 0.0f))
    {
      return {(T)0, (T)0, (T)0, (T)0};
    }

    return quat{in.x() / length, in.y() / length, in.z() / length, in.w() / length};
  }

  /// Find the dot product of a quaternion
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto dot(const quat<T>& in, const quat<T>& other) -> T
  {
    return in.w() * other.w() + in.x() * other.x() + in.y() * other.y() + in.z() * other.z();
  }

  /// Get the inverse of a quaternion
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto invert(const quat<T>& in) -> quat<T>
  {
    quat out{in.x(), in.y(), in.z(), in.w()};
    out = conjugate(out);
    out = normalize(out);
    return out;
  }

  /// Convert a quaternion into euler angles
  /// @return {roll pitch yaw} in radians
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto toEulerRotation(const quat<T>& in) -> vec3<T>
  {
    constexpr T one = (T)1;
    constexpr T two = (T)2;
    const T sinr = two * (in.w() * in.x() + in.y() * in.z());
    const T cosr = one - (two * (in.x() * in.x() + in.y() * in.y()));
    const T roll = std::atan2(sinr, cosr);
    const T sinp = two * (in.w() * in.y() - in.z() * in.x());
    const T siny = two * (in.w() * in.z() + in.x() * in.y());
    const T cosy = one - (two * (in.y() * in.y() + in.z() * in.z()));
    const T yaw = std::atan2(siny, cosy);

    if(std::fabs(sinp) >= 1)
    {
      return {roll, std::copysign(std::numbers::pi / two, sinp), yaw};
    }

    return {roll, std::asin(sinp), yaw};
  }

  /// Convert a quaternion to an axis + angle rotation
  /// @return {x, y, z, radians}
  template <typename T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto toAxial(const quat<T>& in) -> vec4<T>
  {
    const float angle = (T)2 * std::acos(in.w());
    const float divisor = std::sqrt(1 - (in.w() * in.w()));

    if((float)divisor < 0.001f)
    {
      return {in.x(), in.y(), in.z(), angle};
    }

    return {in.x() / divisor, in.y() / divisor, in.z() / divisor, angle};
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto matToQuat(const mat4x4<T>& in) -> quat<T>
  {
    const T trace = in[0][0] + in[1][1] + in[2][2];
    if(trace > 0)
    {
      const T root = (T)2 * std::sqrt(trace + (T)1);
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
      const T root = (T)2 * std::sqrt((T)1 + in[0][0] - in[1][1] - in[2][2]);
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
      const T root = (T)2 * std::sqrt((T)1 + in[1][1] - in[0][0] - in[2][2]);
      return
      {
        (in[0][1] + in[1][0]) / root,
        root / (T)4,
        (in[1][2] + in[2][1]) / root,
        (in[0][2] - in[2][0]) / root
      };
    }

    const T root = (T)2 * std::sqrt((T)1 + in[2][2] - in[0][0] - in[1][1]);
    return
    {
      (in[0][2] + in[2][0]) / root,
      (in[1][2] + in[2][1]) / root,
      root / (T)4,
      (in[1][0] - in[0][1]) / root
    };
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto matToQuat(const mat3x3<T>& in) -> quat<T>
  {
    quat<T> out{};
    const T trace = in[0][0] + in[1][1] + in[2][2];

    if(trace > 0.0f)
    {
      const T root = std::sqrt(trace + (T)1) * (T)2;
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
      const T root = (T)2 * std::sqrt((T)1 + in[0][0] - in[1][1] - in[2][2]);
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
      const T root = (T)2 * std::sqrt((T)1 + in[1][1] - in[0][0] - in[2][2]);
      return
      {
        (in[0][1] + in[1][0]) / root,
        root / (T)4,
        (in[1][2] + in[2][1]) / root,
        (in[0][2] - in[2][0]) / root
      };
    }

    const T root = (T)2 * std::sqrt((T)1 + in[2][2] - in[0][0] - in[1][1]);
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
    const vec2<T> rel,
    const T lookSensitivity) -> quat<T>
  {
    float a = (-rel.x() * lookSensitivity) / 2.0f;
    const quat<T> xQuat{0.0f, std::sin(a), 0.0f, std::cos(a)};
    a = (-rel.y() * lookSensitivity) / 2.0f;
    const quat<T> yQuat(std::sin(a), 0.0f, 0.0f, std::cos(a));
    return normalize(xQuat * yQuat);
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

    return normalize(quat
    {
      cYaw * sRoll * cPitch - sYaw * cRoll * sPitch,
      cYaw * cRoll * sPitch + sYaw * sRoll * cPitch,
      sYaw * cRoll * cPitch - cYaw * sRoll * sPitch,
      cYaw * cRoll * cPitch + sYaw * sRoll * sPitch
    });
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto fromAxialRotation(const vec4<T>& in) -> quat<T>
  {
    const float a = in[3] / (T)2;
    const float s = std::sin(a);

    return normalize(quat
    {
      in[0] * s,
      in[1] * s,
      in[2] * s,
      std::cos(a)
    });
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

    return normalize(quat
    {
      xIn * s,
      yIn * s,
      zIn * s,
      std::cos(a)
    });
  }

  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto fromAxialRotation(
    const vec3<T>& xyzIn,
    const T& angle) -> quat<T>
  {
    const float a = angle / (T)2;
    const float s = std::sin(a);

    return normalize(quat
    {
      xyzIn[0] * s,
      xyzIn[1] * s,
      xyzIn[2] * s,
      std::cos(a)
    });
  }

  /// Find a right handed orientation quaternion that points at the target
  /// OpenGL uses a right handed coordinate system, so this is probably what you'll want to use most often
  /// \param originPos Typically the position of the camera, also called eye
  /// \param targetPos The point in the world to aim at
  /// \param upVec A normalized direction vector specifying what direction up is to be considered
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAtRH(
    const vec3<T>& originPos,
    const vec3<T>& targetPos,
    const vec3<T>& upVec) -> quat<T>
  {
    vec3 forward = originPos - targetPos;
    const T length = mag(forward);

    if(closeEnough(length, (T)0))
    {
      return {};
    }

    normalize(forward);
    vec3 right = normalize(cross(upVec, forward));
    if(closeEnough(dot(right, right), (T)0))
    {
      right = cross(vec3{(T)1, (T)0, (T)0}, forward);
    }

    normalize(right);
    const vec3 orthogonalUp = normalize(cross(forward, right));
    return matToQuat(mat3x3{right, orthogonalUp, forward});
  }

  /// Find a left handed orientation quaternion that points at the target
  /// \param originPos Typically the position of the camera, also called eye
  /// \param targetPos The point in the world to aim at
  /// \param upVec A normalized direction vector specifying what direction up is to be considered
  /// @return An orientation quaternion pointing at the target
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAtLH(
    const vec3<T>& originPos,
    const vec3<T>& targetPos,
    const vec3<T>& upVec) -> quat<T>
  {
    //FIXME rewrite with the 0 checks
    const vec3 forward = normalize(targetPos - originPos);
    const vec3 left = normalize(cross(forward, -upVec));
    const vec3 orthogonalUp = normalize(cross(forward, left));
    return matToQuat(mat3x3{left, orthogonalUp, forward});
  }

  /// A cumulative SLERP version of lookAt, changes the quaternion over time
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto lookAt(
    const vec3<T> originPos,
    const vec3<T> targetPos,
    const quat<T>& currentRotation,
    const T lerp = (T)1) -> quat<T>
  {
    vec3 frontTo = normalize(targetPos - originPos) * conjugate(currentRotation);
    return deltaBetweenVectorsAsRotation({(T)0, (T)0, (T)1}, frontTo, lerp);
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
    const vec3 upQ = normalize(-up * in.conjugated());
    const T dot = dot(vec3{(T)0, (T)1, (T)0}, upQ);

    if(dot >= 1)
    {
      return {};
    }

    if(dot < -1)
    {
      dot = -1;
    }

    T radians = std::acos(dot);
    if(radians > angleLimit)
    {
      return {};
    }

    const vec3 rotAxis = normalize(cross(vec3{(T)0, (T)1, (T)0}, upQ));
    return fromAxialRotation(rotAxis.x(), rotAxis.y(), rotAxis.z(), (angleLimit - radians) * lerp);
  }

  /// Find a quaternion rotation that will rotate the start vector to the end vector along the shortest path
  /// This creates a relative rotation quat, it needs to be multiplied by an orientation quat to change the orientation
  /// @param start Typically a camera's current facing direction (converted from its current quat rotation), or its up vector
  /// @param end Typically where you want a camera to point to, or the corrected up vector, ie the world's up direction
  /// @return A rotation quaternion that will make an orientation quat pointing at start rotate to point to end
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto deltaRotationBetweenVectors(
    const vec3<T>& start,
    const vec3<T>& end) -> quat<T>
  {
    const vec3 startNorm = normalize(start);
    const vec3 endNorm = normalize(end);
    const float cosTheta = dot(startNorm, endNorm);
    vec3<T> axis;

    if(cosTheta < -1.0f + 0.001f)
    {
      axis = cross(vec3{0.0f, 0.0f, 1.0f}, startNorm);
      if(mag(axis) < 0.01f)
      {
        axis = cross(vec3{1.0f, 0.0f, 0.0f}, startNorm);
      }
      normalize(axis);
      return fromAxialRotation(axis, degToRad(180.0f));
    }

    axis = cross(startNorm, endNorm);
    const float root = std::sqrt((1.0f + cosTheta) * 2.0f);
    float invRoot = 1.0f / root;
    return {root * 0.5f, axis.x() * invRoot, axis.y() * invRoot, axis.z() * invRoot};
  }

  /// Reorient a quaternion using an up vector
  /// A common use case for this is to prevent a camera from rolling when moving the mouse in circles
  /// This creates a relative rotation quat, it needs to be multiplied by an orientation quat to change the orientation
  /// @param in The quaternion to orient
  /// @param up The up vector to orient the quaternion to
  /// @return The quaternion that will reorient the input rotation
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto correctOrientation(
    const quat<T>& in,
    const vec3<T>& up) -> quat<T>
  {

    //FIXME something about this is wrong
    const vec3 rotatedUpVec = in * up;
    const quat deltaRotation = deltaRotationBetweenVectors(rotatedUpVec, up);
    return deltaRotation;

    /*const vec3 upQ = (up * in.conjugated()).normalized();
    vec3 side = (vec3{(T)0, (T)0, (T)1}.cross(-upQ)).normalized();

    if(dot(vec3{(T)0, (T)1, (T)0}, upQ) <= 0)
    {
      side = -side;
    }

    vec3 upFixed = vec3{(T)0, (T)0, (T)1}.cross(side).normalized();
    return deltaRotationBetweenVectors({(T)0, (T)1, (T)0}, upFixed);*/
  }
  
  //==Mat3x3============================================================================================================

  //TODO how to invert a 3x3?
  /*
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto invert(const mat3x3<T>& in) -> mat3x3<T>
  {
    const T a = in.z3() * in.w4() - in.w3() * in.z4();
    const T b = in.y3() * in.w4() - in.w3() * in.y4();
    const T c = in.y3() * in.z4() - in.z3() * in.y4();
    const T d = in.x3() * in.w4() - in.w3() * in.x4();
    const T e = in.x3() * in.z4() - in.z3() * in.x4();
    const T f = in.x3() * in.y4() - in.y3() * in.x4();
    const T g = in.z2() * in.w4() - in.w2() * in.z4();
    const T h = in.y2() * in.w4() - in.w2() * in.y4();
    const T i = in.y2() * in.z4() - in.z2() * in.y4();
    const T j = in.z2() * in.w3() - in.w2() * in.z3();
    const T k = in.y2() * in.w3() - in.w2() * in.y3();
    const T l = in.y2() * in.z3() - in.z2() * in.y3();
    const T m = in.x2() * in.w4() - in.w2() * in.x4();
    const T n = in.x2() * in.z4() - in.z2() * in.x4();
    const T o = in.x2() * in.w3() - in.w2() * in.x3();
    const T p = in.x2() * in.z3() - in.z2() * in.x3();
    const T q = in.x2() * in.y4() - in.y2() * in.x4();
    const T r = in.x2() * in.y3() - in.y2() * in.x3();

    T det =   in.x1() * (in.y2() * a - in.z2() * b + in.w2() * c)
            - in.y1() * (in.x2() * a - in.z2() * d + in.w2() * e)
            + in.z1() * (in.x2() * b - in.y2() * d + in.w2() * f)
            - in.w1() * (in.x2() * c - in.y2() * e + in.z2() * f);
    det = (T)1 / det;

    return
    {
      {
        det *  (in.y2() * a - in.z2() * b + in.w2() * c),
        det * -(in.x2() * a - in.z2() * d + in.w2() * e),
        det *  (in.x2() * b - in.y2() * d + in.w2() * f),
        det * -(in.x2() * c - in.y2() * e + in.z2() * f)
      },
      {
        det * -(in.y1() * a - in.z1() * b + in.w1() * c),
        det *  (in.x1() * a - in.z1() * d + in.w1() * e),
        det * -(in.x1() * b - in.y1() * d + in.w1() * f),
        det *  (in.x1() * c - in.y1() * e + in.z1() * f)
      },
      {
        det *  (in.y1() * g - in.z1() * h + in.w1() * i),
        det * -(in.x1() * g - in.z1() * m + in.w1() * n),
        det *  (in.x1() * h - in.y1() * m + in.w1() * q),
        det * -(in.x1() * i - in.y1() * n + in.z1() * q)
      },
      {
        det * -(in.y1() * j - in.z1() * k + in.w1() * l),
        det *  (in.x1() * j - in.z1() * o + in.w1() * p),
        det * -(in.x1() * k - in.y1() * o + in.w1() * r),
        det *  (in.x1() * l - in.y1() * p + in.z1() * r)
      }
    };
  }*/


  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto transpose(const mat3x3<T>& in) -> mat3x3<T>
  {
    return
    {
      {in.x1(), in.x2(), in.x3()},
      {in.y1(), in.y2(), in.y3()},
      {in.z1(), in.z2(), in.z3()},
    };
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mat3x3ToMat4x4(const mat3x3<T>& in) -> mat4x4<T>
  {
    return
    {
      {in.x1(), in.y1(), in.z1(), (T)0},
      {in.x2(), in.y2(), in.z2(), (T)0},
      {in.x3(), in.y3(), in.z3(), (T)0},
      {(T)0,     (T)0,     (T)0,     (T)0}
    };
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto quatToMat3x3(const quat<T>& rotation) -> mat3x3<T>
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
      {sqx - sqy - sqz + sqw, (T)2 * (t1 + t2),       (T)2 * (t3 - t4)},
      {(T)2 * (t1 - t2),      -sqx + sqy - sqz + sqw, (T)2 * (t5 + t6)},
      {(T)2 * (t3 + t4),      (T)2 * (t5 - t6),       -sqx - sqy + sqz + sqw},
    };
  }

  //==Mat4x4============================================================================================================

  /// Calculate the determinant of this mat4x4
  /// @return The determinant value, in the storage type of this mat4x4
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto determinant(const mat4x4<T>& in) -> T
  {
    return
      in.w1() * in.z2() * in.y3() * in.x4() -
      in.z1() * in.w2() * in.y3() * in.x4() -
      in.w1() * in.y2() * in.z3() * in.x4() +
      in.y1() * in.w2() * in.z3() * in.x4() +
      in.z1() * in.y2() * in.w3() * in.x4() -
      in.y1() * in.z2() * in.w3() * in.x4() -
      in.w1() * in.z2() * in.x3() * in.y4() +
      in.z1() * in.w2() * in.x3() * in.y4() +
      in.w1() * in.x2() * in.z3() * in.y4() -
      in.x1() * in.w2() * in.z3() * in.y4() -
      in.z1() * in.x2() * in.w3() * in.y4() +
      in.x1() * in.z2() * in.w3() * in.y4() +
      in.w1() * in.y2() * in.x3() * in.z4() -
      in.y1() * in.w2() * in.x3() * in.z4() -
      in.w1() * in.x2() * in.y3() * in.z4() +
      in.x1() * in.w2() * in.y3() * in.z4() +
      in.y1() * in.x2() * in.w3() * in.z4() -
      in.x1() * in.y2() * in.w3() * in.z4() -
      in.z1() * in.y2() * in.x3() * in.w4() +
      in.y1() * in.z2() * in.x3() * in.w4() +
      in.z1() * in.x2() * in.y3() * in.w4() -
      in.x1() * in.z2() * in.y3() * in.w4() -
      in.y1() * in.x2() * in.z3() * in.w4() +
      in.x1() * in.y2() * in.z3() * in.w4();
  }

  /// Calculate the inverse of this mat4x4
  /// @return A mat4x4 containing the result
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto invert(const mat4x4<T>& in) -> mat4x4<T> requires(IsNumeric<T>)
  {
    const T a = in.z3() * in.w4() - in.w3() * in.z4();
    const T b = in.y3() * in.w4() - in.w3() * in.y4();
    const T c = in.y3() * in.z4() - in.z3() * in.y4();
    const T d = in.x3() * in.w4() - in.w3() * in.x4();
    const T e = in.x3() * in.z4() - in.z3() * in.x4();
    const T f = in.x3() * in.y4() - in.y3() * in.x4();
    const T g = in.z2() * in.w4() - in.w2() * in.z4();
    const T h = in.y2() * in.w4() - in.w2() * in.y4();
    const T i = in.y2() * in.z4() - in.z2() * in.y4();
    const T j = in.z2() * in.w3() - in.w2() * in.z3();
    const T k = in.y2() * in.w3() - in.w2() * in.y3();
    const T l = in.y2() * in.z3() - in.z2() * in.y3();
    const T m = in.x2() * in.w4() - in.w2() * in.x4();
    const T n = in.x2() * in.z4() - in.z2() * in.x4();
    const T o = in.x2() * in.w3() - in.w2() * in.x3();
    const T p = in.x2() * in.z3() - in.z2() * in.x3();
    const T q = in.x2() * in.y4() - in.y2() * in.x4();
    const T r = in.x2() * in.y3() - in.y2() * in.x3();

    T det =   in.x1() * (in.y2() * a - in.z2() * b + in.w2() * c)
            - in.y1() * (in.x2() * a - in.z2() * d + in.w2() * e)
            + in.z1() * (in.x2() * b - in.y2() * d + in.w2() * f)
            - in.w1() * (in.x2() * c - in.y2() * e + in.z2() * f);
    det = (T)1 / det;

    return
    {
      {
        det *  (in.y2() * a - in.z2() * b + in.w2() * c),
        det * -(in.x2() * a - in.z2() * d + in.w2() * e),
        det *  (in.x2() * b - in.y2() * d + in.w2() * f),
        det * -(in.x2() * c - in.y2() * e + in.z2() * f)
      },

      {
        det * -(in.y1() * a - in.z1() * b + in.w1() * c),
        det *  (in.x1() * a - in.z1() * d + in.w1() * e),
        det * -(in.x1() * b - in.y1() * d + in.w1() * f),
        det *  (in.x1() * c - in.y1() * e + in.z1() * f)
      },
      {
        det *  (in.y1() * g - in.z1() * h + in.w1() * i),
        det * -(in.x1() * g - in.z1() * m + in.w1() * n),
        det *  (in.x1() * h - in.y1() * m + in.w1() * q),
        det * -(in.x1() * i - in.y1() * n + in.z1() * q)
      },
      {
        det * -(in.y1() * j - in.z1() * k + in.w1() * l),
        det *  (in.x1() * j - in.z1() * o + in.w1() * p),
        det * -(in.x1() * k - in.y1() * o + in.w1() * r),
        det *  (in.x1() * l - in.y1() * p + in.z1() * r)
      }
    };
  }

  /// Convert this matrix from column-major to row-major or vice-versa
  /// Be careful with this, keep track of which way each matrix is!
  /// @return A mat4x4 containing the result
  template <MathStorageType T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto transposed(const mat4x4<T>& in) -> mat4x4<T>
  {
    return
    {
      {in.x1(), in.x2(), in.x3(), in.x4()},
      {in.y1(), in.y2(), in.y3(), in.y4()},
      {in.z1(), in.z2(), in.z3(), in.z4()},
      {in.w1(), in.w2(), in.w3(), in.w4()}
    };
  }

  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto mat4x4ToMat3x3(const mat4x4<T>& in) -> mat3x3<T>
  {
    return
    {
      {in.x1(), in.y1(), in.z1()},
      {in.x2(), in.y2(), in.z2()},
      {in.x3(), in.y3(), in.z3()}
    };
  }

  /// Convert a quaternion to a 4x4 matrix
  template <IsNumeric T>
  GNUCONST USE_RESULT CANNOT_FAIL
  auto quatToMat4x4(const quat<T>& rotation) -> mat4x4<T>
  {
    const T sqx = rotation.x() * rotation.x();
    const T sqy = rotation.y() * rotation.y();
    const T sqz = rotation.z() * rotation.z();
    const T sqw = rotation.w() * rotation.w();
    const T t1 = rotation.x() * rotation.y();
    const T t2 = rotation.z() * rotation.w();
    const T t3 = rotation.x() * rotation.z();
    const T t4 = rotation.y() * rotation.w();
    const T t5 = rotation.y() * rotation.z();
    const T t6 = rotation.x() * rotation.w();

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
    const mat4x4<T> rotation = quatToMat4x4(invert(cameraRotation));
    const mat4x4<T> translation = translateMat(invert(cameraPosition));
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
