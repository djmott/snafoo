cmake_minimum_required(VERSION 3.8)

project(snafoo)

find_package(Threads)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(3rdParty)

include_directories(3rdParty/XTL/include)
include_directories(3rdParty/AngelScript/sdk/angelscript/include)
include_directories(3rdParty/AngelScript/sdk/add_on)
include_directories(3rdParty/CppSQLite3)
include_directories(${SQLITE_SRC_DIR}/include)
include_directories(3rdParty/JITCompiler)

add_subdirectory(src)
