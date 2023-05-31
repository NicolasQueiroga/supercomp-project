cmake_minimum_required(VERSION 3.5)
project(project VERSION 1.0.1)
enable_language(CUDA)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Og -Wall -pedantic -O3 -fopenmp")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Boost REQUIRED)
find_package(CUDA REQUIRED)
find_package(OpenMP REQUIRED)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)