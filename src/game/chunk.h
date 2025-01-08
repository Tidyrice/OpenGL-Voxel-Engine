#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "block.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include "chunk_pos.h"
#include <mutex>

class World;
struct ChunkPosHash;

class Chunk {
    public:
        // x and z are the chunk coordinates. Chunk(1, 2) will generate the chunk at (CHUNK_WIDTH, 2*CHUNK_WIDTH) to (2*CHUNK_WIDTH-1, 3*CHUNK_WIDTH-1)
        // each chunk is part of a world
        Chunk(ChunkPos pos, World* world);
        ~Chunk();

        void RenderChunk();
        void GenerateMesh(std::unordered_map<ChunkPos, Chunk*, ChunkPosHash>& adjacent_chunk_map);

    private:
        bool IsFaceVisible(const glm::vec3&                                     position,
                           const BlockFace                                      face,
                           std::unordered_map<ChunkPos, Chunk*, ChunkPosHash>&  adjacent_chunk_map) const;
        bool IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const;
        glm::mat4 GetModelMatrix() const;

        std::vector<std::vector<std::vector<BlockEnum::BlockId>>> blocks_; //blocks_[x][y][z]
        ChunkPos pos_;

        std::mutex mesh_mutex_; //mutex to ensure thread safety when generating or rendering mesh
        std::vector<float> vertices_vao_;
        std::vector<int> texture_layers_vao_;
        std::vector<unsigned int> ebo_;

        World* world_;
};


#endif //CHUNK_H
