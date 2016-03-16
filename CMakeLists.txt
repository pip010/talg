cmake_minimum_required(VERSION 2.8)
 
project(talg)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
 
add_executable(talg main.cpp)

set_property(TARGET talg PROPERTY CXX_STANDARD 11)
set_property(TARGET talg PROPERTY CXX_STANDARD_REQUIRED ON)
