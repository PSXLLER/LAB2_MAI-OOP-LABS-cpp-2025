cmake_minimum_required(VERSION 3.14)
project(HexArrayProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(ArrayLib src/Array.cpp)
add_library(HexLib src/Hex.cpp)
target_link_libraries(HexLib PUBLIC ArrayLib)
target_include_directories(ArrayLib PUBLIC include)
target_include_directories(HexLib PUBLIC include)

include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(HexArrayTests tests/test_main.cpp)
target_link_libraries(HexArrayTests PRIVATE HexLib ArrayLib gtest gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(HexArrayTests)

if(MSVC)
  target_compile_options(ArrayLib PRIVATE /W4 /permissive-)
  target_compile_options(HexLib PRIVATE /W4 /permissive-)
  target_compile_options(HexArrayTests PRIVATE /W4 /permissive-)
else()
  target_compile_options(ArrayLib PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(HexLib PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(HexArrayTests PRIVATE -Wall -Wextra -Wpedantic)
endif()