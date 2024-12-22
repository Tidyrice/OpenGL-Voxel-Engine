#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "block.h"
#include <memory>

//This is the interface for the block factory (what the client should use)

class BlockFactory {
    public:
        BlockFactory() = default;
        ~BlockFactory() = default;

        static std::unique_ptr<Block> CreateBlock(BlockId id);
};

#endif // BLOCK_FACTORY_H
