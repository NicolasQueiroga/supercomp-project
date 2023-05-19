cmake_minimum_required(VERSION 3.5)
project(project VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Og -Wall -pedantic -O3 -fopenmp")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Boost REQUIRED)
find_package(CUDA REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(generator ${CMAKE_CURRENT_SOURCE_DIR}/src/generator.cpp)
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(main PUBLIC scheduler greedy random)