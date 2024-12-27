#include "../block_templated.h"

class StoneBlock : public BlockTemplated<StoneBlock> {
    public:
        static constexpr BlockId id_ = BlockId::STONE_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> StoneBlock::texture_layers_ = {
    {BlockFace::X_POS, BlockTexture::STONE},
    {BlockFace::X_NEG, BlockTexture::STONE},
    {BlockFace::Z_POS, BlockTexture::STONE},
    {BlockFace::Z_NEG, BlockTexture::STONE},
    {BlockFace::Y_POS, BlockTexture::STONE},
    {BlockFace::Y_NEG, BlockTexture::STONE},
};