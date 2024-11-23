# Create a library for the scene module
add_library(scene scene.cpp game_scene.cpp)

# Link libraries required by the scene module
target_link_libraries(scene PRIVATE
    view
    freeglut_static
    ${OPENGL_LIBRARIES}
)

# Include directories for this library
target_include_directories(scene PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBRARY_INCLUDE_DIRS}
)
