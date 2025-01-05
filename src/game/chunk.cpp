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
            // for (int i = 0; i < column.size(); i++) {
            //     if (i%5 == 0) {
            //         column[i] = BlockEnum::BlockId::AIR;
            //     }
            // }
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
Chunk::AddVerticiesAndTextureLayers(std::vector<float>& verticies_vao, std::vector<int>& textures_vao,std::vector<unsigned int>& ebo) const
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
                        num_verticies += block->AddVerticies(verticies_vao, ebo, num_verticies, static_cast<BlockFace>(block_face), glm::vec3(i, j, k));
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
    std::vector<unsigned int> indices;

    AddVerticiesAndTextureLayers(vertices_VAO, texture_layers_VAO, indices);

    if (vertices_VAO.size() == 0 || texture_layers_VAO.size() == 0 || indices.size() == 0) {
        std::cerr << "Chunk::RenderChunk(): VAO or EBO is empty" << std::endl;
        return;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);

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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

bool
Chunk::IsFaceVisible(const glm::vec3& position, const BlockFace face) const
{
    Block* neighbour_block;
    
    if (IsFaceOnChunkBorder(position, face)) { //get neighbour block if current block is on chunk border
        if (face == BlockFace::Y_POS || face == BlockFace::Y_NEG) {
            return true;
        }

        ChunkPos neighbour_chunk_pos{0, 0};
        int neighbour_block_x;
        int neighbour_block_z;

        switch (face) {
            case BlockFace::X_POS:
                neighbour_chunk_pos = pos_ + ChunkPos{1, 0};
                neighbour_block_x = 0;
                neighbour_block_z = position.z;
                break;
            case BlockFace::X_NEG:
                neighbour_chunk_pos = pos_ + ChunkPos{-1, 0};
                neighbour_block_x = CHUNK_WIDTH - 1;
                neighbour_block_z = position.z;
                break;
            case BlockFace::Z_POS:
                neighbour_chunk_pos = pos_ + ChunkPos{0, 1};
                neighbour_block_x = position.x;
                neighbour_block_z = 0;
                break;
            case BlockFace::Z_NEG:
                neighbour_chunk_pos = pos_ + ChunkPos{0, -1};
                neighbour_block_x = position.x;
                neighbour_block_z = CHUNK_WIDTH - 1;
                break;
        }

        std::lock_guard<std::mutex> lock(chunk_map_mutex_);
        if (chunk_map_.count(neighbour_chunk_pos) == 0) {
            return true;
        }

        neighbour_block = BlockFactory::GetBlock(chunk_map_.at(neighbour_chunk_pos)->blocks_[neighbour_block_x][position.y][neighbour_block_z]);
    }
    else { //get neighbour block from current chunk
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
