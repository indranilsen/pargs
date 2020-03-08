# Don't need to explicitly add pargs.h since it is a public header
# that is included in top-level CMakeLists.txt (target_include_directories())
# So in pargs.cpp, we can simply call "#import<pargs/pargs.h>"
set(SOURCES pargs.cpp)
add_library(pargs ${SOURCES})