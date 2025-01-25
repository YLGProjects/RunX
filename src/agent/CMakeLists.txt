
project(agent)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

message("Agent Output Dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
list(FILTER SOURCES EXCLUDE REGEX "test")

add_executable(${PROJECT_NAME} ${SOURCES})

list(APPEND LIBS core)
list(APPEND LIBS yaml-cpp)
list(APPEND LIBS event)
list(APPEND LIBS pthread)
list(APPEND LIBS event_openssl)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
