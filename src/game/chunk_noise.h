#ifndef CHUNK_NOISE_H
#define CHUNK_NOISE_H

#include <FastNoise/FastNoise.h>
#include <vector>

class ChunkNoise {
    public:
        ChunkNoise(int seed);
        ~ChunkNoise() = default;

        //output float in range [-1, 1]
        std::vector<float> GenerateChunkNoise(int chunk_x, int chunk_z) const;

    private:
        int seed_;
        FastNoise::SmartNode<FastNoise::Perlin> noise_fn_;
        FastNoise::SmartNode<FastNoise::FractalFBm> generator_;
};

#endif // CHUNK_NOISE_H
