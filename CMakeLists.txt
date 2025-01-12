cmake_minimum_required(VERSION 3.21)
project(tobii-python-zmq)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE libs/vcpkg/scripts/buildsystems/vcpkg.cmake)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "64 bits")
    set(TOBII_LIB_NAME "tobii_gameintegration_x64")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "32 bits")
    set(TOBII_LIB_NAME "tobii_gameintegration_x86")
endif()

find_package(cppzmq REQUIRED)

add_executable(tobii-python-zmq server.cpp)

target_link_libraries(tobii-python-zmq cppzmq)

file(GLOB TOBII_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/tobii_gameintegration_*/include")
file(GLOB TOBII_LIB_FILES "${CMAKE_SOURCE_DIR}/tobii_gameintegration_*/lib/${TOBII_LIB_NAME}.lib")

message(STATUS "Tobii Game Integration include directory: ${TOBII_INCLUDE_DIRS}")
message(STATUS "Tobii Game Integration library files: ${TOBII_LIB_FILES}")

if(TOBII_INCLUDE_DIRS AND TOBII_LIB_FILES)
    target_include_directories(tobii-python-zmq PRIVATE ${TOBII_INCLUDE_DIRS})
    target_link_libraries(tobii-python-zmq ${TOBII_LIB_FILES})
else()
    message(FATAL_ERROR "Tobii Game Integration files not found. Please ensure the correct path is set.")
endif()

add_custom_command(TARGET tobii-python-zmq POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/tobii_gameintegration_9.0.4.26/lib/${TOBII_LIB_NAME}.dll"
        $<TARGET_FILE_DIR:tobii-python-zmq>)

