# Create a library for the controller module
add_library(controller controller.cpp game_controller.cpp)

# Link libraries required by the controller module
target_link_libraries(controller PRIVATE
    view
    freeglut_static
    ${OPENGL_LIBRARIES}
)

# Include directories for this library
target_include_directories(controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBRARY_INCLUDE_DIRS}
)
