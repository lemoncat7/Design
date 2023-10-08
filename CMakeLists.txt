cmake_minimum_required(VERSION 3.15)
project(cplusplus_design_pattern)
set(CMAKE_CXX_STANDARD 11)

set(OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
message(STATUS "output dir : ${OUTPUT_DIR}")
add_subdirectory(SimpleFactory)
add_subdirectory(factoryMethod)