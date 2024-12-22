#include "../block_templated.h"

class StoneBlock : public BlockTemplated<StoneBlock> {
    public:
        static constexpr BlockId id_ = BlockId::STONE_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static std::map<BlockFace, BlockTexture> texture_layers_;
};

std::map<BlockFace, BlockTexture> StoneBlock::texture_layers_ = {
    {BlockFace::FRONT, BlockTexture::STONE},
    {BlockFace::LEFT, BlockTexture::STONE},
    {BlockFace::BACK, BlockTexture::STONE},
    {BlockFace::RIGHT, BlockTexture::STONE},
    {BlockFace::TOP, BlockTexture::STONE},
    {BlockFace::BOTTOM, BlockTexture::STONE},
};