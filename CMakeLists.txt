cmake_minimum_required(VERSION 3.28.3)

project(CalculatorProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    SimpleMathLib
    GIT_REPOSITORY https://github.com/Grozamir/SimpleMathLib
    GIT_TAG master
)

FetchContent_MakeAvailable(SimpleMathLib)

add_executable(calculator src/main.cpp)

target_link_libraries(calculator PRIVATE SimpleMathLib)

file(GLOB_RECURSE ALL_SOURCE_FILES
    src/*.h
    src/*.hpp
    src/*.cpp
)

add_custom_target(
    format
    COMMAND clang-format -i --style=file ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_dependencies(calculator format)


install(TARGETS calculator RUNTIME DESTINATION bin)
