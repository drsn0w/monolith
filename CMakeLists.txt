cmake_minimum_required(VERSION 3.0.0)
project(monolith VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wstrict-prototypes -Wno-unused-function -fsanitize=address")
set(CMAKE_CXX_STANDARD 23)

add_executable(monolith main.cpp monolith.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
