cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snake LANGUAGES CXX)

find_package(SFML 2.5.1 COMPONENTS graphics audio network system REQUIRED)

add_executable(snake src/main.cpp)

target_include_directories(snake PRIVATE inc)

target_link_libraries(snake PRIVATE sfml-graphics sfml-system)

target_compile_options(snake PRIVATE -Werror -Wall -Wextra -pedantic)

target_compile_features(snake PRIVATE cxx_std_23)

