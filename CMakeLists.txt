cmake_minimum_required(VERSION 3.26)
project(AiZO_1)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        service/main.cpp
        service/SortMeasure.cpp
        service/Timer.cpp
        service/FileActions.cpp
        service/RandomArray.cpp
        algorithms/InsertionSort/InsertionSort.cpp
        algorithms/ShellSort/ShellSort.cpp
        algorithms/HeapSort/HeapSort.cpp
        algorithms/QuickSort/QuickSort.cpp
)


add_executable(AiZO_1 ${SOURCE_FILES})

target_include_directories(AiZO_1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/service
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/InsertionSort
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/ShellSort
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/HeapSort
        ${CMAKE_CURRENT_SOURCE_DIR}/algorithms/QuickSort
)

