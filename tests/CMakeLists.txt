set(TESTS_SRC
    main.cc)

add_executable(tests ${TESTS_SRC})
target_include_directories(tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../axm")

include(FetchContent)
FetchContent_Declare(glm
                     GIT_REPOSITORY "https://github.com/g-truc/glm"
                     GIT_TAG "origin/master"
                     SOURCE_DIR "modules/glm")
FetchContent_MakeAvailable(glm)
target_link_libraries(tests PRIVATE axelmath glm::glm)
