cmake_minimum_required(VERSION 3.8)

project(snafoo)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(3rdParty)

include_directories(3rdParty/xtl/include)
include_directories(3rdParty/xtl/include)


add_subdirectory(src)
