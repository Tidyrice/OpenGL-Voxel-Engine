#ifndef CHUNK_POS_HASH_H
#define CHUNK_POS_HASH_H

#include <cstdint>
#include <functional>

struct ChunkPos;

struct ChunkPosHash {
    std::size_t operator()(const ChunkPos& pos) const;
};

#endif // CHUNK_POS_HASH_H