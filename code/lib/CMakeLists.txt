include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR})


add_library(greedy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/greedy/greedy.cpp)

add_library(random SHARED ${CMAKE_CURRENT_SOURCE_DIR}/random/random.cpp)
target_link_libraries(random PUBLIC greedy)

add_library(scheduler SHARED ${CMAKE_CURRENT_SOURCE_DIR}/scheduler/scheduler.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/exaustive)