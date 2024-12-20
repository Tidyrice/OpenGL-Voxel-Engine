#include "../block_templated.h"

class GrassBlock : public BlockTemplated<GrassBlock> {
    public:
        static constexpr BlockId id_ = BlockId::GRASS_BLOCK;
        static constexpr BlockOpacity opacity_ = BlockOpacity::SOLID;
        static constexpr int texture_layers_[] = ;
};