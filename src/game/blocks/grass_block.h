#include "../block_templated.h"

class GrassBlock : public BlockTemplated<GrassBlock> {
    public:
        static constexpr BlockId id_ = BlockId::GRASS_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> GrassBlock::texture_layers_ = {
    {BlockFace::X_POS, BlockTexture::GRASS_SIDE},
    {BlockFace::X_NEG, BlockTexture::GRASS_SIDE},
    {BlockFace::Z_POS, BlockTexture::GRASS_SIDE},
    {BlockFace::Z_NEG, BlockTexture::GRASS_SIDE},
    {BlockFace::Y_POS, BlockTexture::GRASS_TOP},
    {BlockFace::Y_NEG, BlockTexture::DIRT},
};