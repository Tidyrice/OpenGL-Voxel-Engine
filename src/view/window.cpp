#include <glad/glad.h>
#include "window.h"
#include <GL/freeglut.h>
#include "controller.h"
#include "scene.h"
#include "shader.h"
#include <iostream>
#include <stb_image.h>
#include "texture.h"

Window::Window() {
    stbi_set_flip_vertically_on_load(true);
}

void Window::CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s)
{
    glutInitWindowSize(w, h);
    glutInitWindowPosition(pos_x, pos_y);
    windowId_ = glutCreateWindow(window_name.c_str());

    SetScene(s);
}

void Window::InitializeBuffers()
{
    //some temporary data
    float vertices[] = {
        // positions         // colors           // texture coords
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // bottom left
        0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,  // top right
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // textureCoords attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // texture
    tex = new Texture{ASSETS_PATH "/textures/grass_side.png", GL_TEXTURE_2D, GL_TEXTURE0};
    tex->AssignTextureUnit(shader_, "texture0", 0);
}

void Window::RegisterWindowCallbacks() const
{
    if (windowId_ == -1) {
        std::cerr << "Window::RegisterWindowCallbacks(): window not created yet" << std::endl;
        return;
    }

    glutDisplayFunc(RenderSceneCallback);
    glutReshapeFunc(WindowResizeCallback);
    glutIdleFunc(RenderSceneCallback);

    //handle input
    glutKeyboardFunc(Controller::ProcessNormalKeysCallback);
    glutSpecialFunc(Controller::ProcessSpecialKeysCallback);
}

void Window::Clear()
{
    //clears all colours
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);
}


// ---- PRIVATE METHODS ---- //

void Window::RenderSceneCallback()
{
	getInstance().HandleRenderScene();
}

void Window::HandleRenderScene()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_->UseShader();

    tex->Bind();

    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // FILL MODE
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // WIREFRAME MODE
    
    glBindVertexArray(VAO_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glutSwapBuffers();
}

void Window::WindowResizeCallback(int w, int h) //this is needed because GLUT requires non-member or static member functions
{
    getInstance().HandleResize(w, h);
}

void Window::HandleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    windowWidth_ = w;
    windowHeight_ = h;
}
