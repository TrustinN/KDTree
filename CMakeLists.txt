cmake_minimum_required(VERSION 3.29.3)

project(
  "KDTree"
  VERSION 1.0
  DESCRIPTION "A brief CMake experiment"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(main src/main.cpp)

include_directories(build/_deps)
add_subdirectory(tests)
