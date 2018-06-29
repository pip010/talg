cmake_minimum_required(VERSION 3.7)

project(talg VERSION 0.1 LANGUAGES CXX)

add_library(talg INTERFACE)

#target_sources(talg
#    INTERFACE
#        "${CMAKE_CURRENT_LIST_DIR}/src/vector.hpp"
#        "${CMAKE_CURRENT_LIST_DIR}/src/matrix.hpp"
#        "${CMAKE_CURRENT_LIST_DIR}/src/quaternion.hpp"
#        "${CMAKE_CURRENT_LIST_DIR}/src/scalar.hpp"
#		"${CMAKE_CURRENT_LIST_DIR}/src/transform.hpp"
#)



#target_include_directories(talg INTERFACE src/)#../include
target_include_directories(talg INTERFACE	
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:...># can be relative to install path
)

set(CMAKE_CXX_STANDARD 14)

#set(INCLUDE_INSTALL_DIR "")

set(CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/talg")

#set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

#message(STATUS "yyyy:${PROJECT_BINARY_DIR}")

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/TalgConfigVersion.cmake"
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

install(TARGETS talg
    EXPORT TalgTargets
    LIBRARY DESTINATION lib COMPONENT Runtime
    ARCHIVE DESTINATION lib COMPONENT Development
    RUNTIME DESTINATION bin COMPONENT Runtime
    PUBLIC_HEADER DESTINATION include COMPONENT Development
    BUNDLE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Runtime
)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/TalgConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/TalgConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
	#PATH_VARS INCLUDE_INSTALL_DIR
)

install(EXPORT TalgTargets FILE TalgTargets.cmake NAMESPACE talg:: 
		DESTINATION ${CMAKECONFIG_INSTALL_DIR})
 
install(FILES "${PROJECT_BINARY_DIR}/TalgConfigVersion.cmake"
              "${PROJECT_BINARY_DIR}/TalgConfig.cmake"
        DESTINATION ${CMAKECONFIG_INSTALL_DIR})
		
#install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/ DESTINATION include)


ADD_SUBDIRECTORY(tests)

#message(STATUS "xxx:${CMAKECONFIG_INSTALL_DIR}")