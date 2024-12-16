# Create a library for the game module
add_library(game game_scene.cpp)

# Link libraries required by the game module
target_link_libraries(game PRIVATE
    view
    scene
    glfw
    ${OPENGL_LIBRARIES}
)

target_link_libraries(game PUBLIC
    glm
)

# Include directories for this library
target_include_directories(game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
