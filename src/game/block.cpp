#include "block.h"

Block::~Block() {}

uint32_t
Block::AddVerticies(std::vector<float>& vao, std::vector<unsigned int>& ebo, unsigned int num_verticies, const BlockFace face, const glm::vec3& position)
{
    //add verticies to VAO
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
        else { //texture coordinates
            vao.push_back(new_verticies[i]);
        }
    }


    //first triangle
    ebo.push_back(num_verticies);
    ebo.push_back(num_verticies + 1);
    ebo.push_back(num_verticies + 2);
    
    //second triangle
    ebo.push_back(num_verticies + 2);
    ebo.push_back(num_verticies + 3);
    ebo.push_back(num_verticies);

    return 4; //4 verticies per face
}

std::map<BlockFace, std::vector<float>> Block::verticies_map_ = {
    {BlockFace::X_POS, {
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    }},
    {BlockFace::X_NEG, {
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    }},
    {BlockFace::Z_POS, {
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
    }},
    {BlockFace::Z_NEG, {
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
    }},
    {BlockFace::Y_POS, {
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,
    }},
    {BlockFace::Y_NEG, {
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,
    }}
};
