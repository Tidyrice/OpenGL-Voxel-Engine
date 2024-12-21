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
#include <block_enums.h>

//locations of vertex attributes in shader
constexpr uint32_t VERTEX_POS_LOCATION = 0;
constexpr uint32_t TEX_COORD_LOCATION = 1;
constexpr uint32_t TEX_LAYER_LOCATION = 2;

GameScene::GameScene(): Scene{}
{
    camera_ = std::make_unique<Camera>(CAMERA_SPEED, CAMERA_SENSITIVITY);
    model_ = glm::mat4(1.0f);
}

GLuint
GameScene::GenerateArrayTexture()
{
    //temporary stuff until I make a block class
    
    std::vector<std::string> texture_paths = {ASSETS_PATH "/textures/grass_side.png", ASSETS_PATH "/textures/grass_top.png", ASSETS_PATH "/textures/dirt.png", ASSETS_PATH "/textures/stone.png"};
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
    model_ = glm::rotate(model_, GetDeltaTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    //some temporary data
    GLfloat vertices[] = {
        //front
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,

        //left
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,  0.0f,

        //back
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  1.0f,  0.0f,

        //right
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,

        //top
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,

        //bottom
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f
    };

    //can't put these in the float array cause int and float have different bitwise representations
    GLint texture_layers[] = {
        0, 0, 0, 0, 0, 0, //front
        0, 0, 0, 0, 0, 0, //left
        0, 0, 0, 0, 0, 0, //back
        0, 0, 0, 0, 0, 0, //right
        1, 1, 1, 1, 1, 1, //top
        2, 2, 2, 2, 2, 2 //bottom
    };

    unsigned int indices[] = {
        // 0, 1, 2, 2, 3, 0,  // Back face
        // 4, 5, 6, 6, 7, 4,  // Front face
        // 8, 9, 10, 10, 11, 8,  // Left face
        // 12, 13, 14, 14, 15, 12,  // Right face
        // 16, 17, 18, 18, 19, 16,  // Bottom face
        // 20, 21, 22, 22, 23, 20   // Top face
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    // EBO (not currently using)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // POSITION + TEXURE COORDINATES VBO
    glGenBuffers(1, &pos_tex_VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, pos_tex_VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //set pointer to data
    
    glVertexAttribPointer(VERTEX_POS_LOCATION, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); // vertex position
    glEnableVertexAttribArray(VERTEX_POS_LOCATION);
    
    glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); // texture coordinates
    glEnableVertexAttribArray(TEX_COORD_LOCATION);

    // TEXTURE LAYER VBO
    glGenBuffers(1, &layer_VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, layer_VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texture_layers), texture_layers, GL_STATIC_DRAW); //set pointer to data

    glVertexAttribIPointer(TEX_LAYER_LOCATION, 1, GL_INT, 1 * sizeof(int), (void*)0); // texture layer
    glEnableVertexAttribArray(TEX_LAYER_LOCATION);
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
    }
}

void
GameScene::HandleMouseMovement(double x, double y)
{
    camera_->HandleMouseMovement(x, y);
}