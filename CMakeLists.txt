cmake_minimum_required(VERSION 3.10)

project(RunX VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OUTPUT_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(OUTPUT_LIB_DIR ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# load custom modules
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# find_package()

option(BUILD_DEPENDENCIES "Build denpendencies" OFF)
option(BUILD_TESTS "Build test cases" OFF)

string(TIMESTAMP BUILT_TIME "%Y-%m-%d %H:%M:%S")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT DEFINED VERSION)
    set(VERSION "unknown")
endif()

add_definitions(-DRAPIDJSON_HAS_STDSTRING)

include_directories(${CMAKE_BINARY_DIR}/../src)

include_directories(/usr/lib
                    /usr/local/include)

link_directories(/usr/lib
                /usr/lib64
                /usr/local/lib
                /usr/local/lib64)

add_subdirectory(src/core)
add_subdirectory(src/agent)
add_subdirectory(src/server/controller)
add_subdirectory(src/server/transfer)
