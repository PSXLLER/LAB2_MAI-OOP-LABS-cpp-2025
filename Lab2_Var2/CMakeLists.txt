cmake_minimum_required(VERSION 3.14)
project(HexArrayProject LANGUAGES CXX)

# ===== Настройки компилятора =====
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включаем подробные ошибки
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===== Пути к заголовкам =====
include_directories(include)

# ===== Основные библиотеки =====
# Библиотека для Array
add_library(ArrayLib
    src/Array.cpp
)
target_include_directories(ArrayLib PUBLIC include)

# Библиотека для Hex (зависит от Array)
add_library(HexLib
    src/Hex.cpp
)
target_include_directories(HexLib PUBLIC include)
target_link_libraries(HexLib PUBLIC ArrayLib)

# ===== GoogleTest =====
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Для MSVC (Windows) иначе краш
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ===== Тесты =====
add_executable(HexArrayTests
    tests/test_main.cpp
)

target_link_libraries(HexArrayTests
    PRIVATE
        HexLib
        ArrayLib
        gtest
        gtest_main
)

# ===== Автоматическое обнаружение тестов =====
include(GoogleTest)
gtest_discover_tests(HexArrayTests)

# ===== Оптимизации / предупреждения =====
if (MSVC)
    target_compile_options(HexLib PRIVATE /W4 /permissive-)
    target_compile_options(ArrayLib PRIVATE /W4 /permissive-)
    target_compile_options(HexArrayTests PRIVATE /W4 /permissive-)
else()
    target_compile_options(HexLib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(ArrayLib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(HexArrayTests PRIVATE -Wall -Wextra -Wpedantic)
endif()
