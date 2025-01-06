#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "block.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include "chunk_pos.h"
#include "chunk_pos_hash.h"
#include <mutex>

class Chunk {
    public:
        // x and z are the chunk coordinates. Chunk(1, 2) will generate the chunk at (CHUNK_WIDTH, 2*CHUNK_WIDTH) to (2*CHUNK_WIDTH-1, 3*CHUNK_WIDTH-1)
        Chunk(ChunkPos pos);
        ~Chunk();

        void RenderChunk();

    private:
        bool IsFaceVisible(const glm::vec3& position, const BlockFace face) const;
        bool IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const;
        void GenerateVerticiesAndTextureLayers();
        glm::mat4 GetModelMatrix() const;

        static std::unordered_map<ChunkPos, Chunk*, ChunkPosHash> chunk_map_; //holds all active chunks
        static std::mutex chunk_map_mutex_;

        std::vector<std::vector<std::vector<BlockEnum::BlockId>>> blocks_; //blocks_[x][y][z]
        ChunkPos pos_;

        bool is_dirty_ = true; //if the chunk has needs rerendering
        std::vector<float> vertices_vao_;
        std::vector<int> texture_layers_vao_;
        std::vector<unsigned int> ebo_;
};


#endif //CHUNK_H
