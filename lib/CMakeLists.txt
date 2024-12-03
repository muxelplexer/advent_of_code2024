add_library(aoc_lib
    src/conversion.cpp
)

target_include_directories(aoc_lib PUBLIC
    inc/
)

target_link_libraries(aoc_lib PRIVATE
    range-v3
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
set_target_properties(aoc_lib PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_compile_options(aoc_lib PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Weffc++ -Wconversion -Wsign-conversion -fms-extensions
)


set_property(TARGET aoc_lib PROPERTY CXX_STANDARD 23)
set_property(TARGET aoc_lib PROPERTY CXX_EXTENSIONS FALSE)
