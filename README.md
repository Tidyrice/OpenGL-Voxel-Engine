# OpenGL Voxel Engine

A voxel-based application written using OpenGL in C++. It is heavily inspired by Minecraft.

My initial inspriation for this project was to get a better understanding of multithreading, synchronization, and their applications. Chunk and mesh generation in this project are multithreaded, resulting in continuous world generation while rendering without lag.

Other than multithreading, I also learned the inner workings of computer graphics. Some important lessons I learned while debugging were:

* It's expensive to send buffers to the GPU
* OpenGL is NOT thread safe
* Minimize number of vertices using the EBO

One of the coolest things about computer graphics in my opinion are the matrices used to transform objects from local space to world space to view space to clip space and then finally to screen space. I always thought the linear algebra taught in school was useless for software engineers, but turns out it wasn't!

## Screenshots

* Chunk generation occurs on a seperate thread (does not interfere with rendering)
![multithread-terrain](https://github.com/user-attachments/assets/4900d4b9-7017-450a-805c-b0bef5427a93)



## Build using CMake

* Clone the repository
```bash
git clone --recursive https://github.com/Tidyrice/OpenGL-Voxel-Engine.git
```

* Build the project (on Linux or Git Bash)
```bash
cd OpenGL-Voxel-Engine
./scripts/build.sh

# for debug build:
./scripts/build.sh --debug
```

* Run the application on Windows
```bash
.\build\bin\ProcGen.exe
```

* Run the application on Linux
```bash
.\build\bin\ProcGen
```


## Classes of Interest

**Chunk**:

**World**:

**BlockFactory**:

**BlockTemplated**:
