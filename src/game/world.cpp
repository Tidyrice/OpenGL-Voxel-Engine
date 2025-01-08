#include "world.h"
#include "chunk.h"
#include "thread"
#include <iostream>
#include "block.h"

const std::vector<ChunkPos> World::adjacent_chunk_positions_ = {
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};

World::World(ChunkPos pos) : current_chunk_pos_{pos}
{
    AddVisibleChunksToCreationQueue(); //add chunks within render distance to queue (queue is already empty)

    //start chunk creation thread (2)
    for (int i = 0; i < 2; i++) {
        std::thread chunk_creation_thread(&World::ProcessChunkCreationQueueThreaded, this);
        chunk_creation_thread.detach();
    }

    //start chunk mesh generation thread
    std::thread chunk_mesh_gen_thread(&World::ProcessChunkMeshQueueThreaded, this);
    chunk_mesh_gen_thread.detach();
}

World::~World()
{
    terminate_threads_ = true;
}

void
World::RenderWorld()
{
    {
        // std::cout << "World::RenderWorld()" << std::endl;
        std::shared_lock<std::shared_mutex> lock(chunk_map_mutex_);
        // std::cout << "World::RenderWorld(): acquired S lock" << std::endl;

        //render already generated chunks
        for (auto& [pos, chunk] : chunk_map_) { //iterate through chunk map
            chunk->RenderChunk();
        }

        //release shared lock
    }

    //this function acquires unique lock
    ProcessChunkDeletionQueue(); //delete chunks that are outside render distance
}

void
World::UpdateChunkPos(const ChunkPos& pos)
{
    // std::cout << "World::UpdateChunkPos()" << std::endl;
    if (current_chunk_pos_ == pos) {
        return;
    }
    current_chunk_pos_ = pos;
    std::cout << "World::UpdateChunkPos(): new current_chunk_pos_: " << current_chunk_pos_.x << ", " << current_chunk_pos_.z << std::endl;

    chunk_creation_queue_.Clear();
    chunk_mesh_queue_.Clear();
    chunk_deletion_queue_.Clear();

    AddVisibleChunksToCreationQueue();
    AddInvisibleChunksToDeletionQueue();
}

void
World::ProcessChunkCreationQueueThreaded()
{
    while (!terminate_threads_) {
        ChunkPos pos = chunk_creation_queue_.Pop();

        // std::cout << "World::CreateChunkThreaded()" << std::endl;
        std::unique_lock<std::shared_mutex> lock(chunk_map_mutex_);
        // std::cout << "World::CreateChunkThreaded(): acquired X lock" << std::endl;

        if (chunk_map_.count(pos) == 0) { //only execute if chunk doesn't exist
            chunk_map_[pos] = std::make_unique<Chunk>(pos, this); //create chunk
            chunk_mesh_queue_.Push(pos); //generate mesh for chunk
            RegenerateAdjacentChunkMeshes(pos); //let adjacent chunks know to update their meshes
        }
    }
}

void
World::ProcessChunkMeshQueueThreaded()
{
    while (!terminate_threads_) {
        ChunkPos pos = chunk_mesh_queue_.Pop();

        // std::cout << "World::GenerateChunkMeshThreaded()" << std::endl;

        //using shared lock so RenderWorld can render while mesh is being generated
        //Chunk has its own mutex to synchrnize rendering and mesh generation
        std::shared_lock<std::shared_mutex> lock(chunk_map_mutex_);

        // std::cout << "World::GenerateChunkMeshThreaded(): acquired S lock" << std::endl;

        if (chunk_map_.count(pos) != 0) {
            std::unordered_map<ChunkPos, Chunk*, ChunkPosHash> adjacent_chunk_map;
            for (auto& adjacent_pos : adjacent_chunk_positions_) {
                ChunkPos neighbour_pos = pos + adjacent_pos;
                if (chunk_map_.count(neighbour_pos) != 0) {
                    adjacent_chunk_map[neighbour_pos] = chunk_map_.at(neighbour_pos).get();
                }
            }
            chunk_map_.at(pos)->GenerateMesh(adjacent_chunk_map);
        }

        //lock is held until GenerateMesh completes
    }
}

void
World::ProcessChunkDeletionQueue() //NOTE: called from main thread
{
    if (!chunk_deletion_queue_.Empty()) {
        if (chunk_map_mutex_.try_lock()) { //return if mutex is locked to ensure RenderWorld is not blocked

            ChunkPos pos = chunk_deletion_queue_.Pop();
            if (chunk_map_.count(pos) != 0) {
                chunk_map_.erase(pos);
            }

            chunk_map_mutex_.unlock();
        }
    }
}

void
World::AddVisibleChunksToCreationQueue()
{
    for (int i = -renderDistance_; i <= renderDistance_; i++) { //add all chunks in render distance to queue (TODO: CHANGE ORDER OF GENERATION TO NEAREST FIRST)
        for (int j = -renderDistance_; j <= renderDistance_; j++) {
            chunk_creation_queue_.Push({current_chunk_pos_.x + i, current_chunk_pos_.z + j});
        }
    }
}

void
World::AddInvisibleChunksToDeletionQueue()
{
    // std::cout << "World::AddInvisibleChunksToDeletionQueue()" << std::endl;
    std::shared_lock<std::shared_mutex> lock(chunk_map_mutex_);

    for (auto& [pos, chunk] : chunk_map_) { //iterate through chunk map
        if (abs(pos.x - current_chunk_pos_.x) > renderDistance_ || abs(pos.z - current_chunk_pos_.z) > renderDistance_) { //if chunk is outside render distance call dtor
            chunk_deletion_queue_.Push(pos);
        }
    }
}

void
World::RegenerateAdjacentChunkMeshes(const ChunkPos& pos)
{
    for (auto& adjacent_pos : adjacent_chunk_positions_) {
        ChunkPos neighbour_pos = pos + adjacent_pos;
        // std::cout << "World::RegenerateAdjacentChunkMeshes(): neighbour_pos: " << neighbour_pos.x << ", " << neighbour_pos.z << std::endl;
        chunk_mesh_queue_.Push(neighbour_pos);
    }
}