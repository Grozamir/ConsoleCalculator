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

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG master
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG main
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.x
)

FetchContent_MakeAvailable(SimpleMathLib)
FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(spdlog)

find_package(PostgreSQL REQUIRED)

find_package(cppzmq REQUIRED)

add_library(calculator_lib
    src/core/Parser.cpp
    src/core/Checker.cpp
    src/core/Calculator.cpp
    src/core/Printer.cpp
    src/core/Runner.cpp
    src/storage/postgres/Connection.cpp
    src/storage/postgres/Work.cpp
    src/storage/Storage.cpp
    src/storage/Data.cpp
    src/core/Service.cpp
    src/core/Response.cpp
)

target_include_directories(calculator_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(calculator_lib PUBLIC SimpleMathLib nlohmann_json::nlohmann_json spdlog PostgreSQL::PostgreSQL cppzmq)

add_executable(calculator src/main.cpp)
target_link_libraries(calculator PUBLIC calculator_lib)

#target_compile_options(calculator PRIVATE -fsanitize=thread -g -O1)
#target_link_options(calculator PRIVATE -fsanitize=thread)

add_executable(calculator_tests tests/CalculatorTests.cpp
    tests/ServiceTests.cpp)
target_link_libraries(calculator_tests PUBLIC calculator_lib GTest::gtest_main)

add_test(NAME calculator_tests COMMAND calculator_tests)


file(GLOB_RECURSE ALL_SOURCE_FILES
    src/*.h
    src/*.hpp
    src/*.cpp
    tests/*.cpp
)

add_custom_target(
    format
    COMMAND clang-format -i --style=file ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_dependencies(calculator format)

add_custom_target(
    valgrind_test
    COMMAND valgrind --leak-check=full $<TARGET_FILE:calculator> '{"numA":5,"numB":2,"operation":"mul"}'
    DEPENDS calculator
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)


install(TARGETS calculator RUNTIME DESTINATION /usr/bin)

install(FILES calculator.service DESTINATION /etc/systemd/system)

set(CPACK_GENERATOR "DEB")

set(CPACK_PACKAGE_NAME "calculator")
set(CPACK_PACKAGE_VERSION "0.2")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "grozamir")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libzmq5")

include(CPack)
