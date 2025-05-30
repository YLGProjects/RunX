
project(controller)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

message("Server Output Dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../internal/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../internal/*.cc")

list(FILTER SOURCES EXCLUDE REGEX "test")

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(absl REQUIRED COMPONENTS base log)
find_package(protobuf REQUIRED)
find_package(gRPC REQUIRED)
#find_package(etcd-cpp-api REQUIRED)

list(APPEND LIBS core)
list(APPEND LIBS curl)
list(APPEND LIBS yaml-cpp)
list(APPEND LIBS event)
list(APPEND LIBS pthread)
list(APPEND LIBS event_openssl)
list(APPEND LIBS etcd-cpp-api)
list(APPEND LIBS stdc++fs)
list(APPEND LIBS absl::base)
list(APPEND LIBS absl::log)
list(APPEND LIBS gRPC::grpc++)
list(APPEND LIBS cpprest)
list(APPEND LIBS protobuf::libprotobuf)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
