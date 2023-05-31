include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(gpu ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(gpu PUBLIC thrust omp greedy random)


add_executable(generator ${CMAKE_CURRENT_SOURCE_DIR}/generator.cpp)