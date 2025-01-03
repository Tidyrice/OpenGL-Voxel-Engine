#ifndef CHUNK_POS_H
#define CHUNK_POS_H

#include <cstdint>

struct ChunkPos {
    ChunkPos(int64_t x, int64_t z): x{x}, z{z} {}
    bool operator== (const ChunkPos& other) const {
        return x == other.x && z == other.z;
    }
    ChunkPos operator+ (const ChunkPos& other) const {
        return ChunkPos{x + other.x, z + other.z};
    }
    int64_t x, z;
};

#endif //CHUNK_POS_H
