# Create a library for the common module
add_library(common INTERFACE)

# Include directories for this library
target_include_directories(common INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
