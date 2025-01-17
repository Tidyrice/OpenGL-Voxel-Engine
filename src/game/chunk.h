#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "block.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include "chunk_pos.h"
#include <mutex>
#include <GLFW/glfw3.h>
#include "chunk_data.h"

class World;
struct ChunkPosHash;
class ChunkTerrainGenerator;

class Chunk {
    public:
        // x and z are the chunk coordinates. Chunk(1, 2) will generate the chunk at (CHUNK_WIDTH, 2*CHUNK_WIDTH) to (2*CHUNK_WIDTH-1, 3*CHUNK_WIDTH-1)
        // each chunk is part of a world
        Chunk(ChunkPos pos, World* world, const ChunkTerrainGenerator& terrain_generator);
        ~Chunk();

        void RenderChunk();
        void GenerateMesh(std::unordered_map<ChunkPos, Chunk*, ChunkPosHash>& adjacent_chunk_map);

    private:
        bool IsFaceVisible(const glm::vec3&                                     position,
                           const BlockFace                                      face,
                           std::unordered_map<ChunkPos, Chunk*, ChunkPosHash>&  adjacent_chunk_map) const;
        bool IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const;
        glm::mat4 GetModelMatrix() const;

        ChunkData chunk_data_;

        //these methods must only be called from the MAIN THREAD since OpenGL is not thread safe
        void InitializeBuffers();
        void DeleteBuffers();
        bool buffers_initialized_ = false;
        GLuint VAO_, pos_tex_VBO_, tex_layers_VBO_, EBO_;

        std::mutex mesh_mutex_; //mutex to ensure thread safety when generating or rendering mesh
        std::vector<float> vertices_vao_;
        std::vector<int> texture_layers_vao_;
        std::vector<unsigned int> ebo_;

        World* world_;
};


#endif //CHUNK_H
