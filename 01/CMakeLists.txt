add_executable(aoc_day1
    src/main.cpp
)

target_include_directories(aoc_day1 PRIVATE
    inc/
)

target_link_libraries(aoc_day1 PRIVATE
    range-v3
)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}")
set_target_properties(aoc_day1 PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_compile_options(aoc_day1 PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Weffc++ -Wconversion -Wsign-conversion -fms-extensions
)


set_property(TARGET aoc_day1 PROPERTY CXX_STANDARD 23)
set_property(TARGET aoc_day1 PROPERTY CXX_EXTENSIONS FALSE)
