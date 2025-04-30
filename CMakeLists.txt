cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(./SpaceMono-Regular.ttf ./SpaceMono-Regular.ttf COPYONLY)

project(snake LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)

FetchContent_MakeAvailable(sfml)

add_executable(snake src/main.cpp src/game.cpp src/level.cpp src/snake.cpp src/apple.cpp)

target_include_directories(snake PRIVATE inc)

target_link_libraries(snake PRIVATE sfml-system sfml-window sfml-graphics)

target_compile_options(snake PRIVATE -Werror -Wall -Wextra -pedantic)

target_compile_features(snake PRIVATE cxx_std_23)

