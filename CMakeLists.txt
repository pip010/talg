cmake_minimum_required(VERSION 2.8)
 
project(talg)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(src)
SET(SrcFolderListing
src/matrix.hpp
src/vector.hpp
src/scalar.hpp
src/algo.h
src/algo.cpp
)

include_directories(tests)
SET(TestsFolderListing
tests/vector_test.h
tests/matrix_test.h
)
 
add_executable(talg tests/main.cpp ${SrcFolderListing} ${TestsFolderListing})

set_property(TARGET talg PROPERTY CXX_STANDARD 11)
set_property(TARGET talg PROPERTY CXX_STANDARD_REQUIRED ON)



# Includes Catch in the project:
#add_subdirectory(${EXT_PROJECTS_DIR}/catch)
#include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
#enable_testing(true)
