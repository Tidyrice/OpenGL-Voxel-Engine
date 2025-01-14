#include "chunk_data.h"
#include "game_config.h"

ChunkData::ChunkData(ChunkPos pos) : pos_{pos}
{
    blocks_.resize(CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_WIDTH, BlockEnum::BlockId::AIR);
}

void
ChunkData::SetBlock(int x, int y, int z, BlockEnum::BlockId block_id)
{
    blocks_[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT] = block_id;
}

BlockEnum::BlockId
ChunkData::GetBlock(int x, int y, int z) const
{
    return blocks_[x + y * CHUNK_WIDTH + z * CHUNK_WIDTH * CHUNK_HEIGHT];
}