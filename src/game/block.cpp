#include "block.h"

Block::~Block() {}

const std::map<BlockFace, std::vector<float>>&
Block::GetVerticiesVaoMap()
{
    return verticies_map_;
}

//THIS NEEDS TO CHANGE: VERTICIES CAN USE WORLD COORDINATES)
std::map<BlockFace, std::vector<float>> Block::verticies_map_ = {
    {BlockFace::FRONT, {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::LEFT, {
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::BACK, {
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::RIGHT, {
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::TOP, {
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::BOTTOM, {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
    }}
};
