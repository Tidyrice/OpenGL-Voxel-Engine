# Add the main executable
add_executable(${PROJECT_NAME} main.cpp)

# Include directories for the main executable
target_include_directories(${PROJECT_NAME} PUBLIC
    view
    controller
    ### model
    ${LIBRARY_INCLUDE_DIRS}
)

# Add subdirectories
add_subdirectory(view)
add_subdirectory(controller)
### add_subdirectory(model)

# Link libraries and dependencies to the main executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    view
    controller
    freeglut_static
    ${OPENGL_LIBRARIES}
)
