#ifndef CHUNK_POS_H
#define CHUNK_POS_H

#include <cstdint>

struct ChunkPos {
    ChunkPos() = default;
    ChunkPos(int x, int z): x{x}, z{z} {}

    bool operator== (const ChunkPos& other) const {
        return x == other.x && z == other.z;
    }
    ChunkPos operator+ (const ChunkPos& other) const {
        return ChunkPos{x + other.x, z + other.z};
    }

    int x = 0, z = 0;
};

#endif //CHUNK_POS_H
