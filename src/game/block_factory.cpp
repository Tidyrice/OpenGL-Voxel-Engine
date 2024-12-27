#include "block_factory.h"
#include <iostream>
#include "blocks/grass_block.h"
#include "blocks/dirt_block.h"
#include "blocks/stone_block.h"

std::unique_ptr<Block>
BlockFactory::CreateBlock(BlockId id)
{
    switch (id) {
        case BlockId::AIR:
            return nullptr;
            break;
        case BlockId::GRASS_BLOCK:
            return std::make_unique<GrassBlock>();
            break;
        case BlockId::DIRT_BLOCK:
            return std::make_unique<DirtBlock>();
            break;
        case BlockId::STONE_BLOCK:
            return std::make_unique<StoneBlock>();
            break;
        default:
            std::cerr << "BlockFactory::CreateBlock(): Invalid block id" << std::endl;
            exit(-1);
    }
}