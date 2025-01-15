#ifndef CHUNK_NOISE_H
#define CHUNK_NOISE_H

#include <FastNoiseLite.h>
#include <vector>

class ChunkNoise {
    public:
        ChunkNoise(int seed);
        ~ChunkNoise() = default;

        //output float in range [-1, 1]
        std::vector<float> GenerateChunkNoise(int chunk_x, int chunk_z) const;

    private:
        int seed_;
        FastNoiseLite noise_fn_;
};

#endif // CHUNK_NOISE_H
