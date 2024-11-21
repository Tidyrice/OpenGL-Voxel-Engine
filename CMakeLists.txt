cmake_minimum_required(VERSION 3.16)

set (PROJECT_NAME "ProcGen")
set (LIBRARIES_PATH "lib")

project(${PROJECT_NAME} VERSION 1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the main executable
add_executable(${PROJECT_NAME}
    src/main.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Find and link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE freeglut_static ${OPENGL_LIBRARIES})

# Add libs
add_subdirectory(
    ${LIBRARIES_PATH}/freeglut
    ${LIBRARIES_PATH}/glm)

# Include lib headers
target_include_directories(
    ${PROJECT_NAME} PRIVATE ${LIBRARIES_PATH}/freeglut/include
    ${PROJECT_NAME} PRIVATE ${LIBRARIES_PATH}/glm/glm)
