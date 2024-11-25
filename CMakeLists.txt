cmake_minimum_required(VERSION 3.16)

set (PROJECT_NAME "ProcGen")
set(LIBRARIES_PATH "${CMAKE_SOURCE_DIR}/lib")

project(${PROJECT_NAME} VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find and link OpenGL
find_package(OpenGL REQUIRED)

# Set global output directory for all executables to root build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Include lib headers (must be defined BEFORE add_subdirectory)
set(LIBRARY_INCLUDE_DIRS
    ${LIBRARIES_PATH}/freeglut/include
    ${LIBRARIES_PATH}/glm/glm
    ${LIBRARIES_PATH}/glad/include
)

# Include directories globally for all subdirectories
include_directories(${LIBRARY_INCLUDE_DIRS})

# Add libraries and subdirectories
add_subdirectory(${LIBRARIES_PATH}/freeglut)
add_subdirectory(${LIBRARIES_PATH}/glm)
add_subdirectory(${LIBRARIES_PATH}/glad)
add_subdirectory(src)
