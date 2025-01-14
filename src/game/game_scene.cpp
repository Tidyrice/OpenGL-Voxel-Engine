#include <glad/glad.h>
#include "game_scene.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game_config.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <block_texture_map.h>
#include "window.h"
#include "shader.h"
#include "world.h"
#include "game_seed.h"

GameScene::GameScene(): Scene{}
{
    camera_ = std::make_unique<Camera>(CAMERA_SPEED, CAMERA_SENSITIVITY, glm::vec3(0.0f, CHUNK_HEIGHT + 1.0f, 0.0f), CAMERA_YAW, CAMERA_PITCH);
}

GLuint
GameScene::GenerateArrayTexture()
{
    std::vector<std::string> texture_paths;

    //iterate through BlockTexture enum and load textures from the map
    for (int i = 0; i != static_cast<int>(BlockEnum::BlockTexture::END_TEXTURES); i++) {
        texture_paths.push_back(block_texture_map.at(static_cast<BlockEnum::BlockTexture>(i)));
    }
    int tex_width, tex_height, tex_channels;
    std::vector<unsigned char*> texture_data;

    //load textures
    for (const auto& path : texture_paths) {
        unsigned char* data = stbi_load(path.c_str(), &tex_width, &tex_height, &tex_channels, 0);
        if (data) {
            texture_data.push_back(data);
        }
        else {
            std::cerr << "GameScene::GenerateArrayTexture(): Failed to load texture: " << path << std::endl;
        }
    }
    if (texture_data.size() == 0) {
        std::cerr << "GameScene::GenerateArrayTexture(): No textures loaded" << std::endl;
        exit(-1);
    }

    GLuint array_texture;
    glGenTextures(1, &array_texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, array_texture);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST for pixel art
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //allocate storage (found this on stack overflow)
    glTexImage3D(GL_TEXTURE_2D_ARRAY,
                0,                        // level
                GL_RGBA8,                 // Internal format
                tex_width, tex_height, texture_data.size(), // width,height,depth
                0,                        // border?
                GL_RGBA,                  // format
                GL_UNSIGNED_BYTE,         // type
                0);                       // pointer to data

    for (int i = 0; i < texture_data.size(); i++) {
        //send texture data to ith layer of texture array
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, tex_width, tex_height, 1, GL_RGBA, GL_UNSIGNED_BYTE, texture_data[i]);
    }

    for (auto& data : texture_data) {
        stbi_image_free(data);
    }

    glBindTexture(GL_TEXTURE_2D_ARRAY, array_texture);
    return array_texture;
}

void
GameScene::UpdatePerFrame()
{
    std::cout << "GameScene::UpdatePerFrame(): time since last frame: " << GetDeltaTime() * 1000 << " ms" << std::endl;
    std::vector<float> vertices_VAO;
    std::vector<int> texture_layers_VAO;

    camera_->MakeMove(); //update camera position based on key presses

    //calculate which chunk camera is in
    glm::vec3 pos = camera_->GetPosition();
    ChunkPos current_chunk_pos{(int)pos.x / CHUNK_WIDTH, (int)pos.z / CHUNK_WIDTH};

    //render world based on current chunk
    static World world{current_chunk_pos, WORLD_SEED};
    world.UpdateChunkPos(current_chunk_pos);
    world.RenderWorld();
}

void
GameScene::HandleNormalKeys(int key, int action)
{
    if (action == GLFW_RELEASE) {
        return;
    }

    switch (key) {
        case GLFW_KEY_ESCAPE: //escape key
            exit(0);
            break;
        case GLFW_KEY_W:
            camera_->MoveForward();
            break;
        case GLFW_KEY_A:
            camera_->MoveLeft();
            break;
        case GLFW_KEY_S:
            camera_->MoveBackward();
            break;
        case GLFW_KEY_D:
            camera_->MoveRight();
            break;
        case GLFW_KEY_SPACE:
            camera_->MoveUp();
            break;
        case GLFW_KEY_LEFT_SHIFT:
            camera_->MoveDown();
            break;
    }
}

void
GameScene::HandleMouseMovement(double x, double y)
{
    camera_->HandleMouseMovement(x, y);
}