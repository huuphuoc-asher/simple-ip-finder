cmake_minimum_required(VERSION 3.16)
project(mycpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mycpp
  src/main.cpp
)

target_include_directories(mycpp PRIVATE include)

# ----- tests -----
include(CTest)
enable_testing()

add_executable(mycpp_tests
  tests/test_main.cpp
)

add_test(NAME mycpp_tests COMMAND mycpp_tests)
