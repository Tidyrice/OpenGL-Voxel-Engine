#ifndef CHUNK_DATA_H
#define CHUNK_DATA_H

#include <vector>
#include "block_enums.h"
#include "chunk_pos.h"

class ChunkData {
    public:
        ChunkData(ChunkPos pos);
        ~ChunkData() = default;

        void SetBlock(int x, int y, int z, BlockEnum::BlockId block_id);
        BlockEnum::BlockId GetBlock(int x, int y, int z) const;

        ChunkPos GetPos() const { return pos_; }

    private:
        ChunkPos pos_;
        std::vector<BlockEnum::BlockId> blocks_;
};

#endif // CHUNK_DATA_H
