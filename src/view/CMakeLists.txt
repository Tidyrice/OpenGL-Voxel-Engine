# Create a library for the view module
add_library(view window.cpp shader.cpp)

# Link libraries required by the view module
target_link_libraries(view PUBLIC
    freeglut_static
)
target_link_libraries(view PRIVATE
    controller
    scene
    glm
    glad
    stb
    ${OPENGL_LIBRARIES}
)

# Include directories for this library
target_include_directories(view PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
