#ifndef CHUNK_H
#define CHUNK_H

#include <vector>
#include "block.h"
#include <glm/glm.hpp>

class Chunk {
    public:
        Chunk();
        ~Chunk() = default;

        // returns number of verticies added
        uint32_t AddVerticiesAndTextureLayers(std::vector<float>& verticies_vao, std::vector<int>& textures_vao) const;

    private:
        bool IsFaceVisible(const glm::vec3& position, const BlockFace face) const;
        bool IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const;
        std::vector<std::vector<std::vector<BlockEnum::BlockId>>> blocks_; //blocks_[x][y][z]

};


#endif //CHUNK_H
