cmake_minimum_required(VERSION 3.6)

project(containers
  DESCRIPTION "custom C++ containers including hash set, hash map"
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

if (MSVC)
  add_compile_options(/W4 /w14640)
else()
  add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Google Test and Benchmark

FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)

FetchContent_Declare(googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.8.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_TESTING off)  # to suppress benchmark internal tests

FetchContent_MakeAvailable(
  googletest
  googlebenchmark
)

enable_testing()
include(GoogleTest)

# clang-tidy and IWYU must be configured before any declared target
find_program(IWYU_PATH NAMES include-what-you-use iwyu)
find_program(CLANG_TIDY_PATH NAMES clang-tidy)
if(NOT IWYU_PATH)
  message(FATAL_ERROR "Could not find the program include-what-you-use")
endif()
if(NOT CLANG_TIDY_PATH)
  message(FATAL_ERROR "Could not find the program clang-tidy")
endif()
set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PATH};-checks=*")
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})

# Project libraries and targets

add_library(flat_hash_map STATIC src/flat_hash_map.cpp include/flat_hash_map.hpp)
target_include_directories(flat_hash_map PUBLIC include PRIVATE src)

add_executable(flat_hash_map_test test/flat_hash_map_test.cpp)
target_link_libraries(flat_hash_map_test GTest::gtest_main flat_hash_map)

if (MSVC)
  target_compile_options(flat_hash_map_test PRIVATE /fsanitize=address)
  target_link_options(flat_hash_map_test PRIVATE /fsanitize=address)
else()
  target_compile_options(flat_hash_map_test PRIVATE -fsanitize=address,undefined)
  target_link_options(flat_hash_map_test PRIVATE -fsanitize=address,undefined)
endif()
gtest_discover_tests(flat_hash_map_test)

add_executable(flat_hash_map_bm benchmark/flat_hash_map_bm.cpp)
target_link_libraries(flat_hash_map_bm benchmark::benchmark flat_hash_map)

# All target

add_custom_target(check-all
  DEPENDS flat_hash_map_test
  COMMAND $<TARGET_FILE:flat_hash_map_test>
  DEPENDS flat_hash_map_bm
  COMMAND $<TARGET_FILE:flat_hash_map_bm>
)
