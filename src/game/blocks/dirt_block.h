#include "../block_templated.h"

class DirtBlock : public BlockTemplated<DirtBlock> {
    public:
        static constexpr BlockId id_ = BlockId::DIRT_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> DirtBlock::texture_layers_ = {
    {BlockFace::FRONT, BlockTexture::DIRT},
    {BlockFace::LEFT, BlockTexture::DIRT},
    {BlockFace::BACK, BlockTexture::DIRT},
    {BlockFace::RIGHT, BlockTexture::DIRT},
    {BlockFace::TOP, BlockTexture::DIRT},
    {BlockFace::BOTTOM, BlockTexture::DIRT},
};