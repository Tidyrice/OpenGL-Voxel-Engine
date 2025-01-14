#include "chunk_terrain_generator.h"
#include "chunk_data.h"
#include "game_config.h"

ChunkTerrainGenerator::ChunkTerrainGenerator(int seed) : noise_{seed}
{

}

void
ChunkTerrainGenerator::GenerateChunkTerrain(ChunkData& chunk_data, int chunk_x, int chunk_z) const
{
    std::vector<float> noise = noise_.GenerateChunkNoise(chunk_x, chunk_z);

    for (int z = 0; z < CHUNK_WIDTH; z++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            float height = noise[x + z * CHUNK_WIDTH];
            height = (height + 1.0f) / 2.0f; //normalize to [0, 1]
            height *= CHUNK_HEIGHT;

            //stone for everything below height
            for (int y = 0; y < CHUNK_HEIGHT; y++) {
                if (y < height) {
                    chunk_data.SetBlock(x, y, z, BlockEnum::BlockId::GRASS_BLOCK);
                }
                else {
                    chunk_data.SetBlock(x, y, z, BlockEnum::BlockId::AIR);
                }
            }
        }
    }
}