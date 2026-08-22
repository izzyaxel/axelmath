cmake_minimum_required(VERSION 4.3)
project(axelmath)
project(tests)
set(CMAKE_CXX_STANDARD 20)

set(SRC
    axm/aliases.hh
    axm/types/aabb2ds.hh
    axm/types/circle2ds.hh
    axm/concepts.hh
    axm/math.hh
    axm/types/mat4x4s.hh
    axm/types/quaternions.hh
    axm/types/vec2s.hh
    axm/types/vec3s.hh
    axm/types/vec4s.hh
    axm/quatMath.hh
    axm/matrixMath.hh
    axm/shapeMath.hh
    axm/conversion.hh
    axm/types/mat3x3s.hh
)

set(TESTS_SRC
    tests/main.cc)

add_library(axelmath INTERFACE ${SRC})

add_executable(tests ${TESTS_SRC})

#Grab GLM
include(FetchContent)
FetchContent_Declare(libcommons
                     GIT_REPOSITORY "https://github.com/g-truc/glm"
                     GIT_TAG "origin/master"
                     SOURCE_DIR "modules/glm")
FetchContent_MakeAvailable(libcommons)
target_include_directories(tests PRIVATE "${CMAKE_BINARY_DIR}/modules/glm/")
target_include_directories(tests PRIVATE "axm")
