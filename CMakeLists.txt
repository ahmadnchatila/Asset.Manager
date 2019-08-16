cmake_minimum_required (VERSION 3.4)

##
## PROJECT
## name and version
##
project (Asset.Manager C CXX)
include (cmake/Version.cmake)

##
## CONFIGURATION
##
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Add headers to source list
if (${CMAKE_GENERATOR} STREQUAL "Unix Makefiles")
    set (ASSETMANAGER_ADD_HEADERS FALSE)
else()
    set (ASSETMANAGER_ADD_HEADERS TRUE)
endif()

set (src)

include_directories(ext)
include_directories(src)

add_subdirectory (src)
