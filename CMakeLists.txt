cmake_minimum_required(VERSION 3.0.0)
project(monolith VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wstrict-prototypes -Wno-unused-function -fsanitize=address")

add_executable(monolith monolith.cpp)
add_executable(dir monolith.cpp)
add_executable(cat monolith.cpp)
add_executable(du monolith.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
