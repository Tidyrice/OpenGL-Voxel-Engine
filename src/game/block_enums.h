#pragma once

namespace BlockEnum {

enum class BlockId {
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

enum class BlockTexture {
    BEDROCK = 0,
    GRASS_SIDE,
    GRASS_TOP,
    DIRT,
    STONE,
    OAK_SIDE,
    OAK_TOP,
    OAK_LEAVE,
    SAND,
    WATER,
    GLOWSTONE,

    END_TEXTURES //used for iteration
};

enum class BlockOpacity {
    SOLID = 0,
    TRANSPARENT,
    SEMI_TRANSPARENT,
};

enum class BlockFace {
    X_POS = 0,
    X_NEG,
    Z_POS, // positive z comes OUT of the screen
    Z_NEG,
    Y_POS,
    Y_NEG,
};

}