# Create a library for the view module
add_library(view window.cpp shader.cpp texture.cpp)

# Link libraries required by the view module
target_link_libraries(view PUBLIC
    glfw
)
target_link_libraries(view PRIVATE
    controller
    scene
    glad
    stb
    ${OPENGL_LIBRARIES}
)

target_link_libraries(view PUBLIC
    glm
)

# Include directories for this library
target_include_directories(view PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
