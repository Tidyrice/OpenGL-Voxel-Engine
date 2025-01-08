#ifndef WORLD_H
#define WORLD_H

#include "chunk_pos.h"
#include <unordered_map>
#include <mutex>
#include <memory>
#include "game_config.h"
#include "ts_queue.h"
#include "ts_set_queue.h"
#include "chunk_pos_hash.h"
#include <shared_mutex>
#include <glm/glm.hpp>

class Chunk;
class Block;

class World {
    public:
        World(ChunkPos pos);
        ~World();

        void RenderWorld(); //renders the world around the current chunk
        void UpdateChunkPos(const ChunkPos& pos); //specifies new chunk player is in

    private:
        void ProcessChunkCreationQueueThreaded();
        void ProcessChunkMeshQueueThreaded();
        void ProcessChunkDeletionQueue(); //non-blocking: MUST be called from main thread (Chunk::~Chunk() calls OpenGL methods)

        void AddVisibleChunksToCreationQueue();
        void AddInvisibleChunksToDeletionQueue();
        void RegenerateAdjacentChunkMeshes(const ChunkPos& pos);

        ts_queue<ChunkPos> chunk_creation_queue_; //holds chunks that need to be created
        ts_set_queue<ChunkPos, ChunkPosHash> chunk_mesh_queue_; //holds chunks that need to have their mesh generated
        ts_queue<ChunkPos> chunk_deletion_queue_; //holds chunks that need to be deleted
        
        std::unordered_map<ChunkPos, std::unique_ptr<Chunk>, ChunkPosHash> chunk_map_; //holds all active chunks
        std::shared_mutex chunk_map_mutex_;

        ChunkPos current_chunk_pos_; //current chunk the player is in
        int renderDistance_ = RENDER_DISTANCE; //render distance in chunks

        bool terminate_threads_ = false;

        static const std::vector<ChunkPos> adjacent_chunk_positions_;
};

#endif // WORLD_H
