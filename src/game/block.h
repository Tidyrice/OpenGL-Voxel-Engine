#ifndef BLOCK_H
#define BLOCK_H

enum BlockId {
    AIR = 0,
    BEDROCK,
    GRASS_BLOCK,
    DIRT_BLOCK,
    STONE_BLOCK,
    OAK_BLOCK,
    OAK_LEAVE,
    SAND_BLOCK,
    WATER_BLOCK,
    GLOWSTONE_BLOCK,
};

enum BlockOpacity {
    SOLID = 0,
    TRANSPARENT,
    SEMI_TRANSPARENT,
};

#include <vector>

class Block {
    public:
        Block() = default;
        virtual ~Block() = 0;

        virtual BlockId GetId() const = 0;
        virtual BlockOpacity GetOpacity() const = 0;
        std::vector<float> GetVertices() const;

    private:
        //layers returned in the order: FRONT, LEFT, BACK, RIGHT, TOP, BOTTOM
        virtual const int* GetTextureLayers() const = 0;
};

#endif // BLOCK_H
