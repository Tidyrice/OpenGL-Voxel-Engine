#include "block_factory.h"
#include <iostream>

std::unique_ptr<Block>
BlockFactory::CreateBlock(BlockId id)
{
    switch (id) {
        case BlockId::GRASS_BLOCK:
            return std::make_unique<GrassBlock>(texture_data);
        case BlockId::DIRT_BLOCK:
            return std::make_unique<DirtBlock>(texture_data);
        case BlockId::STONE_BLOCK:
            return std::make_unique<StoneBlock>(texture_data);
        default:
            std::cerr << "BlockFactory::CreateBlock(): Invalid block id" << std::endl;
            exit(-1);
    }
}