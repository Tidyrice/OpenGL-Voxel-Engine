#include "world.h"
#include "chunk.h"
#include "thread"
#include <iostream>

World::World(ChunkPos pos) : current_chunk_pos_{pos}
{
    AddVisibleChunksToCreationQueue(); //add chunks within render distance to queue (queue is already empty)

    //start chunk generation thread
    std::thread chunk_gen_thread(&World::CreateChunkThreaded, this);
    chunk_gen_thread.detach();

    //start chunk mesh generation thread
    std::thread chunk_mesh_gen_thread(&World::GenerateChunkMeshThreaded, this);
    chunk_mesh_gen_thread.detach();

    //start chunk deletion thread
    std::thread chunk_deletion_thread(&World::DeleteChunkThreaded, this);
    chunk_deletion_thread.detach();
}

World::~World()
{
    terminate_threads_ = true;
}

void
World::RenderWorld()
{
    //TODO: have to get rid of this lock somehow. Maybe have a separate thread that renders the world. Causing lagspikes when moving chunks
    std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);

    //render already generated chunks
    for (auto& [pos, chunk] : chunk_map_) { //iterate through chunk map
        chunk->RenderChunk();
    }
}

const Chunk*
World::GetChunk(const ChunkPos& pos)
{
    std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
    if (chunk_map_.count(pos) == 0) {
        return nullptr;
    }
    return chunk_map_.at(pos).get();
}

void
World::UpdateChunkPos(const ChunkPos& pos)
{
    if (current_chunk_pos_ == pos) {
        return;
    }
    current_chunk_pos_ = pos;
    std::cout << "World::UpdateChunkPos(): current_chunk_pos_: " << current_chunk_pos_.x << ", " << current_chunk_pos_.z << std::endl;

    chunk_creation_queue_.Clear();
    chunk_mesh_queue_.Clear();
    chunk_deletion_queue_.Clear();

    AddVisibleChunksToCreationQueue();
    AddInvisibleChunksToDeletionQueue();
}

void
World::CreateChunkThreaded()
{
    while (!terminate_threads_) {
        ChunkPos pos = chunk_creation_queue_.Pop();

        std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
        if (chunk_map_.count(pos) == 0) { //only execute if chunk doesn't exist
            chunk_map_[pos] = std::make_unique<Chunk>(pos, this); //create chunk
            chunk_mesh_queue_.Push(pos); //generate mesh for chunk
            RegenerateAdjacentChunkMeshes(pos); //let adjacent chunks know to update their meshes
        }
    }
}

void
World::GenerateChunkMeshThreaded()
{
    while (!terminate_threads_) {
        ChunkPos pos = chunk_mesh_queue_.Pop();

        std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
        if (chunk_map_.count(pos) != 0) {
            chunk_map_.at(pos)->GenerateMesh();
        }
    }
}

void
World::DeleteChunkThreaded()
{
    while (!terminate_threads_) {
        ChunkPos pos = chunk_deletion_queue_.Pop();

        std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
        if (chunk_map_.count(pos) != 0) {
            chunk_map_.erase(pos);
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
    std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);

    for (auto& [pos, chunk] : chunk_map_) { //iterate through chunk map
        if (abs(pos.x - current_chunk_pos_.x) > renderDistance_ || abs(pos.z - current_chunk_pos_.z) > renderDistance_) { //if chunk is outside render distance call dtor
            chunk_deletion_queue_.Push(pos);
        }
    }
}

void
World::RegenerateAdjacentChunkMeshes(const ChunkPos& pos)
{
    static const std::vector<ChunkPos> adjacent_chunk_positions = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    for (auto& adjacent_pos : adjacent_chunk_positions) {
        ChunkPos neighbour_pos = pos + adjacent_pos;
        chunk_mesh_queue_.Push(neighbour_pos);
    }
}