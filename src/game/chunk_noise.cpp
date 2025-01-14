#include "chunk_noise.h"
#include <FastNoise/Generators/Fractal.h>
#include <FastNoise/FastNoise.h>
#include <game_config.h>
#include <iostream>

ChunkNoise::ChunkNoise(int seed) : seed_(seed)
{
    noise_fn_ = FastNoise::New<FastNoise::Perlin>();
    generator_ = FastNoise::New<FastNoise::FractalFBm>();

    generator_->SetSource(noise_fn_);
    generator_->SetOctaveCount(5);

    generator_->SetGain(0.5f); //amplitude of each octave (compared to previous)
    generator_->SetLacunarity(2.0f); //frequency of each octave (compared to previous)
}

std::vector<float>
ChunkNoise::GenerateChunkNoise(int chunk_x, int chunk_z) const
{
    std::vector<float> noise(CHUNK_WIDTH * CHUNK_WIDTH);
    generator_->GenUniformGrid2D(noise.data(), chunk_x * CHUNK_WIDTH, chunk_z * CHUNK_WIDTH, CHUNK_WIDTH, CHUNK_WIDTH, 0.01f, seed_);
    return noise;
}