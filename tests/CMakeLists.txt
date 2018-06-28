project(talg-tests VERSION 0.1 LANGUAGES CXX)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#include_directories(src)
#SET(SrcFolderListing
#src/matrix.hpp
#src/vector.hpp
#src/scalar.hpp
#src/quaternion.hpp
#src/algos.hpp
#src/matrix_types.hpp
#src/vector_types.hpp
#)





#include_directories(tests)
SET(TestsFolderListing
vector_test.cpp
matrix_test.cpp
scalar_test.cpp
quaternion_test.cpp
main.cpp
)

add_executable(talg-tests ${TestsFolderListing})

#find_package(talg CONFIG REQUIRED)

target_link_libraries(talg-tests talg) # installed include/ path automatically added


set_property(TARGET talg-tests PROPERTY CXX_STANDARD 14)
set_property(TARGET talg-tests PROPERTY CXX_STANDARD_REQUIRED ON)

# Includes Catch in the project:
#add_subdirectory(${EXT_PROJECTS_DIR}/catch)
#include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
#enable_testing(true)