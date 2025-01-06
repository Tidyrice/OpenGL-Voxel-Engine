#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

# Define build directory
BUILD_DIR="build"

# Parse arguments
CLEAN=false
BUILD_TYPE="Release"
for arg in "$@"; do
    if [ "$arg" == "--clean" ]; then
        CLEAN=true
    fi
    if [ "$arg" == "--debug" ]; then
        BUILD_TYPE="Debug"
    fi
done

echo "Starting build process..."

# Step 1: Clean up existing build directory if --clean is specified
if [ "$CLEAN" = true ]; then
    if [ -d "$BUILD_DIR" ]; then
        echo "Removing existing build directory..."
        rm -rf "$BUILD_DIR"
    fi
fi

# Step 2: Create a new build directory
echo "Creating new build directory..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Step 3: Run CMake to generate the build system
echo "Running CMake..."
echo "Build type: $BUILD_TYPE"
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

# Step 4: Build the project
echo "Building the project..."
cmake --build . --config $BUILD_TYPE

# Return to the project root
cd ..

echo "Build process completed successfully!"
