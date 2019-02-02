# CMake version minimum required.
cmake_minimum_required (VERSION 2.8)

# Project name, change it you need.
project (Demo)

# Combine source files to DIR_SRCS in current forld.
aux_source_directory(. DIR_SRCS)

#add_subdirectory(include)

#include_directories(./includ)

# Specify name to be build.
add_executable(Demo ${DIR_SRCS})

# Link libs
target_link_libraries(Demo m)
target_link_libraries(Demo pthread)
