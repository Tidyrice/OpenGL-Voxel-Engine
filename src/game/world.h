#ifndef WORLD_H
#define WORLD_H

#include "chunk_pos.h"
#include "chunk_pos_hash.h"
#include <unordered_map>
#include <mutex>
#include <memory>
#include <queue>
#include "game_config.h"

class Chunk;

class World {
    public:
        World(ChunkPos pos);
        ~World();

        void RenderWorld(); //renders the world around the current chunk
        Chunk* GetChunk(const ChunkPos& pos);
        void UpdateChunkPos(const ChunkPos& pos);

    private:
        void GenerateChunkThreaded(); //called by additional threads
        void AddToChunkQueue(const ChunkPos& pos);
        void AddVisibleChunksToQueue();
        void RegenerateAdjacentChunkVertices(const ChunkPos& pos);

        std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash> chunk_map_; //holds all active chunks
        std::recursive_mutex chunk_map_mutex_;

        std::queue<ChunkPos> chunk_queue_; //holds chunks that need to be generated
        std::recursive_mutex chunk_queue_mutex_;

        ChunkPos current_chunk_pos_; //current chunk the player is in
        int renderDistance_ = RENDER_DISTANCE; //render distance in chunks
};

#endif // WORLD_H
