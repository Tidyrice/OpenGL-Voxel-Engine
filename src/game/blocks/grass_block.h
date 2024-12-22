#include "../block_templated.h"

class GrassBlock : public BlockTemplated<GrassBlock> {
    public:
        static constexpr BlockId id_ = BlockId::GRASS_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> GrassBlock::texture_layers_ = {
    {BlockFace::FRONT, BlockTexture::GRASS_SIDE},
    {BlockFace::LEFT, BlockTexture::GRASS_SIDE},
    {BlockFace::BACK, BlockTexture::GRASS_SIDE},
    {BlockFace::RIGHT, BlockTexture::GRASS_SIDE},
    {BlockFace::TOP, BlockTexture::GRASS_TOP},
    {BlockFace::BOTTOM, BlockTexture::DIRT},
};