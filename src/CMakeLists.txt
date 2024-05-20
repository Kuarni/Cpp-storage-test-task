add_subdirectory(tapeSorterLib)
include_directories(tapeSorterLib)

add_executable(tape_sorter CLI/tape_sorter.cpp)
target_link_libraries(tape_sorter PUBLIC TapeSorter)