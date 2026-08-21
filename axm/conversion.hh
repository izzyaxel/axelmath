#pragma once

#if __has_include("glm.hpp")
#include "aliases.hh"

#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat4x4.hpp"
#include "gtc/quaternion.hpp"

#include "types/vec2s.hh"
#include "types/vec3s.hh"
#include "types/vec4s.hh"
#include "types/mat4x4s.hh"
#include "types/quaternions.hh"

namespace axm
{

  template <typename T> concept IsVec2 = std::same_as<T, vec2<float>> || std::same_as<T, glm::vec2>;
  template <typename T> concept IsVec3 = std::same_as<T, vec3<float>> || std::same_as<T, glm::vec3>;
  template <typename T> concept IsVec4 = std::same_as<T, vec4<float>> || std::same_as<T, glm::vec4>;
  template <typename T> concept IsQuat = std::same_as<T, quat<float>> || std::same_as<T, glm::quat>;
  template <typename T> concept IsMat4x4 = std::same_as<T, mat4x4<float>> || std::same_as<T, glm::mat4x4>;

  template <IsVec2 T1, IsVec2 T2>
  CONST USE_RESULT CANNOT_FAIL
  auto convertVec2(const T1& in) -> T2 requires(!std::same_as<T1, T2>)
  {
    return {in[0], in[1]};
  }

  template <IsVec3 T1, IsVec3 T2>
  CONST USE_RESULT CANNOT_FAIL
  auto convertVec3(const T1& in) -> T2 requires(!std::same_as<T1, T2>)
  {
    return {in[0], in[1], in[2]};
  }

  template <IsVec4 T1, IsVec4 T2>
  CONST USE_RESULT CANNOT_FAIL
  auto convertVec3(const T1& in) -> T2 requires(!std::same_as<T1, T2>)
  {
    return {in[0], in[1], in[2], in[3]};
  }

  template <IsQuat T1, IsQuat T2>
  CONST USE_RESULT CANNOT_FAIL
  auto convertVec3(const T1& in) -> T2 requires(!std::same_as<T1, T2>)
  {
    return {in[0], in[1], in[2], in[3]};
  }

  template <IsVec4 T1, IsVec4 T2>
  CONST USE_RESULT CANNOT_FAIL
  auto convertMat4x4(const T1& in) -> T2 requires(!std::same_as<T1, T2>)
  {
    return
    {
      in[0][0], in[0][1], in[0][2], in[0][3],
      in[1][0], in[1][1], in[1][2], in[1][3],
      in[2][0], in[2][1], in[2][2], in[2][3],
      in[3][0], in[3][1], in[3][2], in[3][3]
    };
  }
}
#endif
