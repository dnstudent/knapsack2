cmake_minimum_required(VERSION 3.17)

project(knapsack LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(KNAPSACK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)
set(KNAPSACK_HEADERS
    ${KNAPSACK_INCLUDE_DIR}/knapsack/definitions.hpp
        ${KNAPSACK_INCLUDE_DIR}/knapsack/simple/recursive.hpp
        ${KNAPSACK_INCLUDE_DIR}/knapsack/simple/dynamic.hpp)

add_library(knapsack INTERFACE)

target_sources(knapsack INTERFACE ${KNAPSACK_HEADERS})
target_include_directories(knapsack INTERFACE ${KNAPSACK_INCLUDE_DIR})
target_compile_options(knapsack INTERFACE -Werror -Wall -Wextra)

set(BUILD_TESTS ON)
enable_testing()
add_subdirectory(test)
#add_subdirectory(benchmark)


include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS knapsack EXPORT ${PROJECT_NAME}-targets)
export(EXPORT ${PROJECT_NAME}-targets FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake")
install(FILES ${KNAPSACK_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/knapsack)

set(KNAPSACK_CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE
    STRING "install path for knapsackConfig.cmake")

configure_package_config_file(${PROJECT_NAME}Config.cmake.in
                              "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
                              INSTALL_DESTINATION ${KNAPSACK_CMAKECONFIG_INSTALL_DIR})
