add_library(greedy SHARED ${CMAKE_CURRENT_SOURCE_DIR}/greedy/greedy.cpp)
add_library(random SHARED ${CMAKE_CURRENT_SOURCE_DIR}/random/random.cpp)
add_library(scheduler SHARED ${CMAKE_CURRENT_SOURCE_DIR}/scheduler/scheduler.cpp)

target_include_directories(greedy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(random PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(scheduler PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR})
