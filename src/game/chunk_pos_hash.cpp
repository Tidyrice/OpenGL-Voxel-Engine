#include "chunk_pos_hash.h"
#include "chunk_pos.h"

std::size_t ChunkPosHash::operator()(const ChunkPos& pos) const {
    std::size_t x_hash = std::hash<uint32_t>{}(pos.x);
    std::size_t z_hash = std::hash<uint32_t>{}(pos.z);
    return x_hash ^ (z_hash << 1); //XOR and bitshift for combining
}