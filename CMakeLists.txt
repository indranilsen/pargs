cmake_minimum_required(VERSION 3.14)
project(pargs)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)

# Add properties to the pargs target
# We need the headers in include/ and src/ to build the library.
# Users only need the public header.
#
# So, INCLUDE_DIRS contains both src/ and include/ while
# INTERFACE_INCLUDE_DIRS only contains include/
#
# While building pargs include/ is at $HOME/PATH_TO_PROJECT/pargs/include/,
# but after installing, the library will be under ${CMAKE_INSTALL_PREFIX/include/}.
# So the location of this dir needs to change if we are building or installing. Hence,
# we use generator expressions to correctly set teh path depending on the situation.
target_include_directories(pargs
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# Do not include CTest if pargs is used a library in another project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

enable_testing()
add_subdirectory(test)