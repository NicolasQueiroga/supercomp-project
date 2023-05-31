include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../include ${CMAKE_CURRENT_SOURCE_DIR})

add_library(omp SHARED ${CMAKE_CURRENT_SOURCE_DIR}/omp/exaustive.cpp)
target_link_libraries(omp PUBLIC scheduler)

add_library(thrust SHARED ${CMAKE_CURRENT_SOURCE_DIR}/thrust/exaustive.cu)
set_target_properties(thrust PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(thrust PUBLIC ${CUDA_LIBRARIES} scheduler)
