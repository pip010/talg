cmake_minimum_required(VERSION 2.8)

project(talg)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(src)
SET(SrcFolderListing
src/matrix.hpp
src/vector.hpp
src/scalar.hpp
src/quaternion.hpp
src/algos.hpp
src/matrix_types.hpp
src/vector_types.hpp
)

include_directories(tests)
SET(TestsFolderListing
tests/vector_test.cpp
tests/matrix_test.cpp
tests/scalar_test.cpp
tests/quaternion_test.cpp
tests/main.cpp
)

add_executable(talg ${SrcFolderListing} ${TestsFolderListing})

set_property(TARGET talg PROPERTY CXX_STANDARD 14)
set_property(TARGET talg PROPERTY CXX_STANDARD_REQUIRED ON)



# Includes Catch in the project:
#add_subdirectory(${EXT_PROJECTS_DIR}/catch)
#include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
#enable_testing(true)
