#include "block_factory.h"
#include <iostream>
#include "blocks/grass_block.h"

std::unique_ptr<Block>
BlockFactory::CreateBlock(BlockId id)
{
    switch (id) {
        case BlockId::GRASS_BLOCK:
            return std::make_unique<GrassBlock>();
            break;
        default:
            std::cerr << "BlockFactory::CreateBlock(): Invalid block id" << std::endl;
            exit(-1);
    }
}