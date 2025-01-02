#include <glad/glad.h>
#include "chunk.h"
#include "game_config.h"
#include "block_factory.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "window.h"
#include "shader.h"

std::unordered_map<ChunkPos, Chunk*, ChunkPosHash> Chunk::chunk_map_;
std::mutex Chunk::chunk_map_mutex_;

Chunk::Chunk(ChunkPos pos) : pos_{pos}
{
    //currently makes a fun pattern

    BlockEnum::BlockId block_id = BlockEnum::BlockId::GRASS_BLOCK;

    blocks_.resize(CHUNK_WIDTH);
    for (auto& row : blocks_) {
        row.resize(CHUNK_HEIGHT);
        for (auto& column : row) {
            column.resize(CHUNK_WIDTH, block_id);
            for (int i = 0; i < column.size(); i++) {
                if (i%5 == 0) {
                    column[i] = BlockEnum::BlockId::AIR;
                }
            }
        }
    }

    std::lock_guard<std::mutex> lock(chunk_map_mutex_);
    chunk_map_[pos_] = this;
}

Chunk::~Chunk()
{
    std::lock_guard<std::mutex> lock(chunk_map_mutex_);
    chunk_map_.erase(pos_);
}

uint32_t
Chunk::AddVerticiesAndTextureLayers(std::vector<float>& verticies_vao, std::vector<int>& textures_vao) const
{
    int num_verticies = 0;
    for (int i = 0; i < CHUNK_WIDTH; i++) {
        for (int j = 0; j < CHUNK_HEIGHT; j++) {
            for (int k = 0; k < CHUNK_WIDTH; k++) {
                if (blocks_[i][j][k] == BlockEnum::BlockId::AIR) {
                    continue;
                }
                for (int block_face = 0; block_face < 6; block_face++) {
                    if (IsFaceVisible(glm::vec3(i, j, k), static_cast<BlockFace>(block_face))) {
                        Block* block = BlockFactory::GetBlock(blocks_[i][j][k]);
                        num_verticies += block->AddVerticies(verticies_vao, static_cast<BlockFace>(block_face), glm::vec3(i, j, k));
                        block->AddTextureLayers(textures_vao, static_cast<BlockFace>(block_face));
                    }
                }
            }
        }
    }
    return num_verticies;
}

void
Chunk::RenderChunk() const
{
    GLuint VAO, EBO;
    std::vector<float> vertices_VAO;
    std::vector<int> texture_layers_VAO;

    uint32_t num_verticies = AddVerticiesAndTextureLayers(vertices_VAO, texture_layers_VAO);

    // unsigned int indices[] = {
    //     0, 1, 2, 2, 3, 0,  // Back face
    //     4, 5, 6, 6, 7, 4,  // Front face
    //     8, 9, 10, 10, 11, 8,  // Left face
    //     12, 13, 14, 14, 15, 12,  // Right face
    //     16, 17, 18, 18, 19, 16,  // Bottom face
    //     20, 21, 22, 22, 23, 20   // Top face
    // };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // // EBO (not currently using)
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // POSITION + TEXURE COORDINATES VBO
    GLuint pos_tex_VBO;
    glGenBuffers(1, &pos_tex_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, pos_tex_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices_VAO.size(), &vertices_VAO[0], GL_STATIC_DRAW); //set pointer to data
    
    glVertexAttribPointer(VERTEX_POS_LOCATION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // vertex position
    glEnableVertexAttribArray(VERTEX_POS_LOCATION);
    
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // texture coordinates
    glEnableVertexAttribArray(TEX_COORD_LOCATION);

    // TEXTURE LAYER VBO
    GLuint layer_VBO;
    glGenBuffers(1, &layer_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, layer_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int)*texture_layers_VAO.size(), &texture_layers_VAO[0], GL_STATIC_DRAW); //set pointer to data

    glVertexAttribIPointer(TEX_LAYER_LOCATION, 1, GL_INT, 1 * sizeof(int), (void*)0); // texture layer
    glEnableVertexAttribArray(TEX_LAYER_LOCATION);

    //send model matrix to shader
    Window::GetActiveWindow()->GetShader().SetMat4("model", GetModelMatrix());

    //render
    glDrawArrays(GL_TRIANGLES, 0, num_verticies);
}

bool
Chunk::IsFaceVisible(const glm::vec3& position, const BlockFace face) const
{
    if (IsFaceOnChunkBorder(position, face)) {
        return true;
    }

    Block* neighbour_block;

    switch (face) {
        case BlockFace::X_POS:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x + 1][position.y][position.z]);
            break;
        case BlockFace::X_NEG:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x - 1][position.y][position.z]);
            break;
        case BlockFace::Z_POS:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x][position.y][position.z + 1]);
            break;
        case BlockFace::Z_NEG:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x][position.y][position.z - 1]);
            break;
        case BlockFace::Y_POS:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x][position.y + 1][position.z]);
            break;
        case BlockFace::Y_NEG:
            neighbour_block = BlockFactory::GetBlock(blocks_[position.x][position.y - 1][position.z]);
            break;
    }

    //if neighbour block is nullptr then it's air (transparent)
    if (!neighbour_block || neighbour_block->GetOpacity() != BlockEnum::BlockOpacity::SOLID) {
        return true;
    }

    return false;
}

bool
Chunk::IsFaceOnChunkBorder(const glm::vec3& position, const BlockFace face) const
{
    if (position.x == 0 && face == BlockFace::X_NEG) {
        return true;
    }
    else if (position.x == CHUNK_WIDTH - 1 && face == BlockFace::X_POS) {
        return true;
    }
    else if (position.y == 0 && face == BlockFace::Y_NEG) {
        return true;
    }
    else if (position.y == CHUNK_HEIGHT - 1 && face == BlockFace::Y_POS) {
        return true;
    }
    else if (position.z == 0 && face == BlockFace::Z_NEG) {
        return true;
    }
    else if (position.z == CHUNK_WIDTH - 1 && face == BlockFace::Z_POS) {
        return true;
    }

    return false;
}

glm::mat4
Chunk::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(pos_.x * CHUNK_WIDTH, 0.0f, pos_.z * CHUNK_WIDTH));
    return model;
}
