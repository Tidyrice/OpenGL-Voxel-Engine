#include "chunk.h"
#include "game_config.h"
#include "block_factory.h"
#include <iostream>

Chunk::Chunk()
{
    //currently makes a fun pattern

    BlockEnum::BlockId block_id = BlockEnum::BlockId::GRASS_BLOCK;

    blocks_.resize(CHUNK_WIDTH);
    for (auto& row : blocks_) {
        row.resize(CHUNK_HEIGHT);
        for (auto& column : row) {
            column.resize(CHUNK_WIDTH, block_id);
            for (int i = 0; i < column.size(); i++) {
                if (i%5 == 0) {
                    column[i] = BlockEnum::BlockId::AIR;
                }
            }
        }
    }
}

uint32_t
Chunk::AddVerticiesAndTextureLayers(std::vector<float>& verticies_vao, std::vector<int>& textures_vao) const
{
    int num_verticies = 0;
    for (int i = 0; i < CHUNK_WIDTH; i++) {
        for (int j = 0; j < CHUNK_HEIGHT; j++) {
            for (int k = 0; k < CHUNK_WIDTH; k++) {
                if (blocks_[i][j][k] == BlockEnum::BlockId::AIR) {
                    continue;
                }
                for (int block_face = 0; block_face < 6; block_face++) {
                    if (IsFaceVisible(glm::vec3(i, j, k), static_cast<BlockFace>(block_face))) {
                        std::unique_ptr<Block> block = BlockFactory::CreateBlock(blocks_[i][j][k]);
                        num_verticies += block->AddVerticies(verticies_vao, static_cast<BlockFace>(block_face), glm::vec3(i, j, k));
                        block->AddTextureLayers(textures_vao, static_cast<BlockFace>(block_face));
                    }
                }
            }
        }
    }
    return num_verticies;
}

bool
Chunk::IsFaceVisible(const glm::vec3& position, const BlockFace face) const
{
    if (IsFaceOnChunkBorder(position, face)) {
        return true;
    }

    std::unique_ptr<Block> neighbour_block;

    switch (face) {
        case BlockFace::X_POS:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x + 1][position.y][position.z]);
            break;
        case BlockFace::X_NEG:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x - 1][position.y][position.z]);
            break;
        case BlockFace::Z_POS:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x][position.y][position.z + 1]);
            break;
        case BlockFace::Z_NEG:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x][position.y][position.z - 1]);
            break;
        case BlockFace::Y_POS:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x][position.y + 1][position.z]);
            break;
        case BlockFace::Y_NEG:
            neighbour_block = BlockFactory::CreateBlock(blocks_[position.x][position.y - 1][position.z]);
            break;
    }

    //if neighbour block is nullptr then it's air (transparent)
    if (!neighbour_block || neighbour_block->GetOpacity() != BlockEnum::BlockOpacity::SOLID) {
        return true;
    }

    return false;
}

bool
Chunk::IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const
{
    if (position.x == 0 && face == BlockFace::X_NEG) {
        return true;
    }
    else if (position.x == CHUNK_WIDTH - 1 && face == BlockFace::X_POS) {
        return true;
    }
    else if (position.y == 0 && face == BlockFace::Y_NEG) {
        return true;
    }
    else if (position.y == CHUNK_HEIGHT - 1 && face == BlockFace::Y_POS) {
        return true;
    }
    else if (position.z == 0 && face == BlockFace::Z_NEG) {
        return true;
    }
    else if (position.z == CHUNK_WIDTH - 1 && face == BlockFace::Z_POS) {
        return true;
    }

    return false;
}