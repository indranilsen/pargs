cmake_minimum_required(VERSION 3.14)
project(pargs)

set(CMAKE_CXX_STANDARD 14)

# This allows test subdirectory to find headers
include_directories(src)

add_subdirectory(src)

# Do not include CTest if pargs is used a library in another project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

enable_testing()
add_subdirectory(test)