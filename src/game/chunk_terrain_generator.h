#ifndef CHUNK_TERRAIN_GENERATOR_H
#define CHUNK_TERRAIN_GENERATOR_H

#include "chunk_noise.h"

class ChunkData;

class ChunkTerrainGenerator {
    public:
        ChunkTerrainGenerator(int seed);
        ~ChunkTerrainGenerator() = default;

        void GenerateChunkTerrain(ChunkData& chunk_data, int chunk_x, int chunk_z) const;

    private:
        ChunkNoise noise_;
};

#endif // CHUNK_GENERATOR_H
