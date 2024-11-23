# Add the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Add subdirectories
add_subdirectory(view)

# Link libraries and include directories
target_link_libraries(${PROJECT_NAME} PRIVATE
    view
    freeglut_static
    ${OPENGL_LIBRARIES}
)

# Include directories for this library
target_include_directories(${PROJECT_NAME} PRIVATE
    ${LIBRARY_INCLUDE_DIRS}
)
