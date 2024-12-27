#include "../block_templated.h"

class DirtBlock : public BlockTemplated<DirtBlock> {
    public:
        static constexpr BlockId id_ = BlockId::DIRT_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> DirtBlock::texture_layers_ = {
    {BlockFace::X_POS, BlockTexture::DIRT},
    {BlockFace::X_NEG, BlockTexture::DIRT},
    {BlockFace::Z_POS, BlockTexture::DIRT},
    {BlockFace::Z_NEG, BlockTexture::DIRT},
    {BlockFace::Y_POS, BlockTexture::DIRT},
    {BlockFace::Y_NEG, BlockTexture::DIRT},
};