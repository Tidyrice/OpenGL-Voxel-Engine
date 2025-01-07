# Create a library for the game module
add_library(game game_scene.cpp block_factory.cpp block.cpp block_texture_map.h chunk.cpp chunk_pos_hash.cpp world.cpp)
target_compile_definitions(game PRIVATE TEXTURES_PATH="${ASSETS_PATH}/textures")
target_compile_definitions(game PRIVATE VERTEX_POS_LOCATION=0)
target_compile_definitions(game PRIVATE TEX_COORD_LOCATION=1)
target_compile_definitions(game PRIVATE TEX_LAYER_LOCATION=2)

# Link libraries required by the game module
target_link_libraries(game PRIVATE
    view
    scene
    glfw
    common
    ${OPENGL_LIBRARIES}
)

target_link_libraries(game PUBLIC
    glm
)

# Include directories for this library
target_include_directories(game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
