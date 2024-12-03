cmake_minimum_required(VERSION 3.29)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
project(aoc_2024
        VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
        range
        GIT_REPOSITORY "https://github.com/ericniebler/range-v3"
        GIT_SHALLOW TRUE
        SYSTEM
)
FetchContent_MakeAvailable(range)

add_subdirectory(lib)
add_subdirectory(01)
