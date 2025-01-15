#include "chunk_noise.h"
#include <FastNoiseLite.h>
#include "game_config.h"
#include "chunk_noise_config.h"

ChunkNoise::ChunkNoise(int seed) : seed_(seed)
{
    noise_fn_.SetSeed(seed);
    noise_fn_.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

    noise_fn_.SetFractalType(FastNoiseLite::FractalType_FBm);
    noise_fn_.SetFractalOctaves(OCTAVES);
    noise_fn_.SetFrequency(FREQUENCY);
    noise_fn_.SetFractalGain(GAIN);
    noise_fn_.SetFractalLacunarity(LACUNARITY);
}

std::vector<float>
ChunkNoise::GenerateChunkNoise(int chunk_x, int chunk_z) const
{
    std::vector<float> noise(CHUNK_WIDTH * CHUNK_WIDTH);

    for (int z = 0; z < CHUNK_WIDTH; z++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            float height = noise_fn_.GetNoise(float(chunk_x * CHUNK_WIDTH + x), float(chunk_z * CHUNK_WIDTH + z));
            noise[x + z * CHUNK_WIDTH] = height;
        }
    }

    return noise;
}