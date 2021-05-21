project(knapsack-benchmark LANGUAGES CXX)
set(KNAPSACK_INCLUDE_DIR ${knapsack_INCLUDE_DIRS})

configure_file(downloadGBenchmark.cmake.in googlebenchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download )
if(result)
    message(FATAL_ERROR "CMake step for googlebenchmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download )
if(result)
    message(FATAL_ERROR "Build step for googlebenchmark failed: ${result}")
endif()

# Add googlebenchmark directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-src
                    ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-build)

set(GBENCHMARK_INCLUDE_DIRS "${googlebenchmark_SOURCE_DIR}/include")
set(GBENCHMARK_LIBRARIES benchmark)

include_directories(${KNAPSACK_INCLUDE_DIR})
include_directories(${GBENCHMARK_INCLUDE_DIRS})

add_executable(knapsack_benchmark knapsack_benchmark.cpp)
target_link_libraries(knapsack_benchmark knapsack ${GBENCHMARK_LIBRARIES})
