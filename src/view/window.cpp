#include <glad/glad.h>
#include "window.h"
#include <GL/freeglut.h>
#include "controller.h"
#include "scene.h"
#include "shader.h"
#include <iostream>
#include <stb_image.h>
#include "texture.h"
#include <glm/glm.hpp>

Window*
Window::GetActiveWindow(Window* instance) //static method
{
    static Window* active_instance = nullptr;
    if (instance != nullptr) {
        active_instance = instance;
    }
    return active_instance;
}

Window::Window(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s) {
    stbi_set_flip_vertically_on_load(true);

    glutInitWindowSize(w, h);
    window_width_ = w;
    window_height_ = h;
    glutInitWindowPosition(pos_x, pos_y);
    window_id_ = glutCreateWindow(window_name.c_str());

    SetScene(s);
}

void
Window::InitializeBuffers()
{
    //some temporary data
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,   // First triangle
        2, 1, 3    // Second triangle
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // textureCoords attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture
    tex = new Texture{ASSETS_PATH "/textures/grass_side.png", GL_TEXTURE_2D, GL_TEXTURE0};
    tex->AssignTextureUnit(shader_, "texture0", 0);
}

void
Window::RegisterWindowCallbacks()
{
    if (window_id_ == -1) {
        std::cerr << "Window::RegisterWindowCallbacks(): window not created yet" << std::endl;
        return;
    }

    //send projection matrix to shader (set here since projecion matrix is constant)
    if (shader_ == nullptr) {
        std::cerr << "Window::RegisterWindowCallbacks(): shader not set" << std::endl;
        return;
    }
    
    shader_->SetMat4("projection", GetProjectionMatrix());

    //handle rendering
    glutDisplayFunc(RenderSceneCallback);
    glutReshapeFunc(WindowResizeCallback);
    glutIdleFunc(RenderSceneCallback);

    //handle input
    glutKeyboardFunc(Controller::ProcessNormalKeysCallback);
    glutSpecialFunc(Controller::ProcessSpecialKeysCallback);
}

void
Window::Clear()
{
    //clears all colours
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);
}


// ---- PRIVATE METHODS ---- //

void
Window::RenderSceneCallback()
{
	GetActiveWindow()->HandleRenderScene();
}

void Window::HandleRenderScene()
{
    scene_->Update(); //let scene know that there is a new frame

    //clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->UseShader();

    tex->Bind();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // FILL MODE
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // WIREFRAME MODE

    //send model matrix to shader
    shader_->SetMat4("model", GetModelMatrix());

    //send view matrix to shader
    shader_->SetMat4("view", GetViewMatrix());

    //render
    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glutSwapBuffers();
    UpdateDeltaTime();
}

void
Window::WindowResizeCallback(int w, int h) //this is needed because GLUT requires non-member or static member functions
{
    GetActiveWindow()->HandleResize(w, h);
}

void Window::HandleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    window_width_ = w;
    window_height_ = h;
}

const glm::mat4&
Window::GetModelMatrix() const
{
    return scene_->GetModelMatrix();
}

const glm::mat4&
Window::GetViewMatrix() const
{
    return scene_->GetViewMatrix();
}

const glm::mat4&
Window::GetProjectionMatrix() const
{
    return scene_->GetProjectionMatrix();
}

void
Window::UpdateDeltaTime()
{
    float current_frame = glutGet(GLUT_ELAPSED_TIME);
    delta_time_ = current_frame - last_frame_;
    last_frame_ = current_frame;
}
