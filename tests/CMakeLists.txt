project(talg-tests VERSION 0.1 LANGUAGES CXX)

SET(TalgLibListing
${CMAKE_SOURCE_DIR}/src/scalar.hpp 
${CMAKE_SOURCE_DIR}/src/vector.hpp 
${CMAKE_SOURCE_DIR}/src/matrix.hpp 
${CMAKE_SOURCE_DIR}/src/quaternion.hpp
${CMAKE_SOURCE_DIR}/src/transform.hpp
${CMAKE_SOURCE_DIR}/src/matrix_types.hpp
${CMAKE_SOURCE_DIR}/src/vector_types.hpp
${CMAKE_SOURCE_DIR}/src/algos.hpp
)

SET(TestsListing
vector_test.cpp
matrix_test.cpp
scalar_test.cpp
quaternion_test.cpp
transform_test.cpp
helpers.h
helpers.cpp
main.cpp
)

add_executable(talg-tests ${TestsListing} ${TalgLibListing})

SOURCE_GROUP("headers" FILES ${TalgLibListing})
SOURCE_GROUP("tests" FILES ${TestsListing})

#find_package(talg CONFIG REQUIRED)

target_link_libraries(talg-tests talg) # installed include/ path automatically added


set_property(TARGET talg-tests PROPERTY CXX_STANDARD 14)
set_property(TARGET talg-tests PROPERTY CXX_STANDARD_REQUIRED ON)

# Includes Catch in the project:
#add_subdirectory(${EXT_PROJECTS_DIR}/catch)
#include_directories(${CATCH_INCLUDE_DIR} ${COMMON_INCLUDES})
#enable_testing(true)