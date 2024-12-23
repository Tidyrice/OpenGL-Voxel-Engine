#include "block.h"

Block::~Block() {}

void
Block::AddVerticies(std::vector<float>& vao, const BlockFace face, const glm::vec3& position)
{
    std::vector<float>& new_verticies = verticies_map_.at(face);

    for (int i = 0; i < new_verticies.size(); i++) {
        if (i % 5 == 0) {
            vao.push_back(new_verticies[i] + position.x);
        }
        else if (i % 5  == 1) {
            vao.push_back(new_verticies[i] + position.y);
        }
        else if (i % 5 == 2) {
            vao.push_back(new_verticies[i] + position.z);
        }
        else {
            vao.push_back(new_verticies[i]);
        }
    }
}

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
