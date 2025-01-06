#include "world.h"
#include "chunk.h"
#include "thread"
#include <iostream>

World::World(ChunkPos pos) : current_chunk_pos_{pos}
{
    AddVisibleChunksToQueue();

    //start threads
    const auto processor_count = std::thread::hardware_concurrency();
    std::cout << "World::World(): processor_count: " << processor_count << std::endl;
    for (int i = 0; i < processor_count-1; i++) {
        std::thread t(GenerateChunkThreaded, this);
        t.detach();
    }
}

World::~World()
{
}

void
World::RenderWorld()
{
    //TODO: have to get rid of this lock somehow. Maybe have a separate thread that renders the world. Causing lagspikes when moving chunks
    std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);

    //render already generated chunks
    for (auto& [pos, chunk] : chunk_map_) { //iterate through chunk map
        if (abs(pos.x - current_chunk_pos_.x) > renderDistance_ || abs(pos.z - current_chunk_pos_.z) > renderDistance_) { //if chunk is outside render distance call dtor
            chunk_map_.erase(pos);
        }
        else {
            chunk->RenderChunk();
        }
    }
}

Chunk*
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

    AddVisibleChunksToQueue();
}

void
World::GenerateChunkThreaded()
{
    while (true) {
        ChunkPos pos;
        {
            std::lock_guard<std::recursive_mutex> lock(chunk_queue_mutex_);
            if (chunk_queue_.empty()) {
                continue;
            }
            pos = chunk_queue_.front();
            chunk_queue_.pop();
        }

        std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
        // if chunk already exists, then do nothing
        if (chunk_map_.count(pos) == 0) {
            chunk_map_[pos] = std::make_unique<Chunk>(pos, this);
            chunk_map_[pos]->GenerateChunkVerticies();
            RegenerateAdjacentChunkVertices(pos);
        }
    }
}

void
World::AddToChunkQueue(const ChunkPos& pos)
{
    std::lock_guard<std::recursive_mutex> lock(chunk_queue_mutex_);
    chunk_queue_.push(pos);
}

void
World::AddVisibleChunksToQueue()
{
    std::lock_guard<std::recursive_mutex> lock(chunk_queue_mutex_);
    chunk_queue_ = std::queue<ChunkPos>(); //clear queue
    for (int i = -renderDistance_; i <= renderDistance_; i++) { //add all chunks in render distance to queue (TODO: CHANGE ORDER OF GENERATION TO NEAREST FIRST)
        for (int j = -renderDistance_; j <= renderDistance_; j++) {
            AddToChunkQueue({current_chunk_pos_.x + i, current_chunk_pos_.z + j});
        }
    }
}

void
World::RegenerateAdjacentChunkVertices(const ChunkPos& pos)
{
    static const std::vector<ChunkPos> adjacent_chunk_positions = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    std::lock_guard<std::recursive_mutex> lock(chunk_map_mutex_);
    for (auto& adjacent_pos : adjacent_chunk_positions) {
        ChunkPos neighbour_pos = pos + adjacent_pos;
        if (chunk_map_.count(neighbour_pos) != 0) {
            chunk_map_[neighbour_pos]->GenerateChunkVerticies();
        }
    }
}