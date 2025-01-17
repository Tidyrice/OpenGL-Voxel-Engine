#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <map>
#include <string>
#include "block_enums.h"
#include <glm/glm.hpp>

using namespace BlockEnum;

class Block {
    public:
        Block() = default;
        virtual ~Block() = 0;

        virtual BlockId GetId() const = 0;
        virtual BlockOpacity GetOpacity() const = 0;

        //appends verticies (position + texture coordinates) for the face for the block at the specified coordinates (in chunk space)
        //returns number of verticies added
        static uint32_t AddVerticies(std::vector<float>&         vao,
                                     std::vector<unsigned int>&  ebo,
                                     unsigned int                num_verticies,
                                     const BlockFace             face,
                                     const glm::vec3&            position);

        //appends texture layers for the specified block face
        virtual void AddTextureLayers(std::vector<int>& vao, const BlockFace face) const = 0;

    private:
        //verticies are in counter clockwise order
        static std::map<BlockFace, std::vector<float>> verticies_map_;
};

#endif // BLOCK_H
