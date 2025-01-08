#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include "block.h"
#include <memory>
#include <unordered_map>

//This is the interface for the block factory (what the client should use)
//uses flyweight pattern to create blocks

class BlockFactory {
    public:
        BlockFactory() = delete;
        ~BlockFactory() = delete;

        static const Block* GetBlock(BlockId id);

    private:
        static std::unique_ptr<Block> CreateBlock(BlockId id);
        static std::unordered_map<BlockId, std::unique_ptr<Block>> block_map_;
};

#endif // BLOCK_FACTORY_H
