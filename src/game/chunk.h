#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "block.h"
#include <glm/glm.hpp>

class Chunk {
    public:
        // x and z are the chunk coordinates. Chunk(1, 2) will generate the chunk at (CHUNK_WIDTH, 2*CHUNK_WIDTH) to (2*CHUNK_WIDTH-1, 3*CHUNK_WIDTH-1)
        Chunk(uint32_t x, uint32_t z);
        ~Chunk() = default;

        void RenderChunk() const;

    private:
        bool IsFaceVisible(const glm::vec3& position, const BlockFace face) const;
        bool IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const;
        uint32_t AddVerticiesAndTextureLayers(std::vector<float>& verticies_vao, std::vector<int>& textures_vao) const; // returns number of verticies added
        glm::mat4 GetModelMatrix() const;

        std::vector<std::vector<std::vector<BlockEnum::BlockId>>> blocks_; //blocks_[x][y][z]
        uint32_t x_, z_;
};


#endif //CHUNK_H
