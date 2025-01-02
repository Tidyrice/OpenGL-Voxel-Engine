#ifndef CHUNK_POS_H
#define CHUNK_POS_H

#include <cstdint>

struct ChunkPos {
    ChunkPos(uint32_t x, uint32_t z): x{x}, z{z} {}
    bool operator== (const ChunkPos& other) const {
        return x == other.x && z == other.z;
    }
    uint32_t x, z;
};

#endif //CHUNK_POS_H
