# Create a library for the view module
add_library(view window.cpp)

# Link libraries required by the view module
target_link_libraries(view PRIVATE
    freeglut_static
    ${OPENGL_LIBRARIES}
)

# Include directories for this library
target_include_directories(view PRIVATE
    ${LIBRARY_INCLUDE_DIRS}
)
