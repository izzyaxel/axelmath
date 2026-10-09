cmake_minimum_required(VERSION 4.3)

project(axelmath VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    axm/aliases.hh
    axm/collisions.hh
    axm/concepts.hh
    axm/conversion.hh
    axm/interpolation.hh
    axm/math.hh
    
    axm/types/aabb2ds.hh
    axm/types/aabb3ds.hh
    axm/types/circles.hh
    axm/types/mat3x3s.hh
    axm/types/mat4x4s.hh
    axm/types/quaternions.hh
    axm/types/spheres.hh
    axm/types/vec2s.hh
    axm/types/vec3s.hh
    axm/types/vec4s.hh
    axm/logging.hh
    axm/meta.hh
)

set(MODULES
  axm/modules/Collisions.ixx
  axm/modules/Conversion.ixx
  axm/modules/Interpolation.ixx
  axm/modules/Math.ixx
  
  axm/modules/types/AABB2ds.ixx
  axm/modules/types/AABB3ds.ixx
  axm/modules/types/Circles.ixx
  axm/modules/types/Mat3x3s.ixx
  axm/modules/types/Mat4x4s.ixx
  axm/modules/types/Quaternions.ixx
  axm/modules/types/Spheres.ixx
  axm/modules/types/Vec2s.ixx
  axm/modules/types/Vec3s.ixx
  axm/modules/types/Vec4s.ixx
)

add_library(axelmath OBJECT ${SRC})
target_sources(axelmath PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES ${MODULES})
target_include_directories(axelmath INTERFACE
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                           $<INSTALL_INTERFACE:include>)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  add_subdirectory(tests)
endif()