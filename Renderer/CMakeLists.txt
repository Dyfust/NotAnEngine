cmake_minimum_required(VERSION 3.10)
project(NotAnEngine)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/${PROJECT_NAME})
set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)
set(PROJECT_VENDOR_DIR ${PROJECT_DIR}/vendor)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/bin)

message(${PROJECT_DIR})

set(CMAKE_SUPPRESS_REGENERATION true)

include_directories(${PROJECT_VENDOR_DIR}/glcore)
include_directories(${PROJECT_VENDOR_DIR}/glfw/GLFW)
include_directories(${PROJECT_VENDOR_DIR}/glm)
include_directories(${PROJECT_VENDOR_DIR}/obj_loader)
include_directories(${PROJECT_VENDOR_DIR}/stb_image)

link_directories(${PROJECT_VENDOR_DIR}/glfw)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/*.h" "${PROJECT_VENDOR_DIR}/glcore/*.c" "${PROJECT_VENDOR_DIR}/glcore/*.h")
add_executable(NotAnEngine ${SOURCES})
target_link_libraries(NotAnEngine opengl32 glfw3)