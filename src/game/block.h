#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <map>
#include <string>
#include "block_enums.h"

using namespace BlockEnum;

class Block {
    public:
        Block() = default;
        virtual ~Block() = 0;

        virtual BlockId GetId() const = 0;
        virtual BlockOpacity GetOpacity() const = 0;
        const std::map<BlockFace, std::vector<float>>& GetVerticiesVaoMap() const; //contains vertex positions and texture coordinates
        virtual const std::map<BlockFace, std::vector<int>>& GetTextureLayersVaoMap() const = 0; //layers returned in the order: FRONT, LEFT, BACK, RIGHT, TOP, BOTTOM

    private:
        static std::map<BlockFace, std::vector<float>> verticies_map_;
};

#endif // BLOCK_H
