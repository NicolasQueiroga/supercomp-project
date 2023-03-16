cmake_minimum_required(VERSION 3.5)
project(project VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 11)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Og -Wall -pedantic -O3")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

find_package(Boost REQUIRED)

add_executable(generator src/generator.cpp)
add_executable(main src/main.cpp)

add_library(greedy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/greedy/greedy.cpp)
add_library(random SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/random/random.cpp)
add_library(scheduler SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/scheduler/scheduler.cpp)

target_include_directories(greedy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(random PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(scheduler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(main PUBLIC scheduler greedy random)
