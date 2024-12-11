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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Window* Window::GetActiveWindow(Window* instance) //static method
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

    //initialize model matrix
    model_ = glm::mat4(1.0f);
    model_ = glm::rotate(model_, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    //initialize view matrix
    view_ = glm::mat4(1.0f);
    view_ = glm::translate(view_, glm::vec3(0.0f, 0.0f, -3.0f)); 

    //initialize projection matrix
    projection_ = glm::mat4(1.0f);
    projection_ = glm::perspective(glm::radians(45.0f), (float)w/(float)h, 0.1f, 100.0f);
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

void Window::RegisterWindowCallbacks()
{
    if (window_id_ == -1) {
        std::cerr << "Window::RegisterWindowCallbacks(): window not created yet" << std::endl;
        return;
    }

    //generate and send projection matrix to shader (set here since projecion matrix is constant)
    InitializeProjectionMatrix();
    shader_->SetMat4("projection", projection_);

    //handle rendering
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
	GetActiveWindow()->HandleRenderScene();
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

    //generate and send model matrix to shader
    InitializeModelMatrix();
    shader_->SetMat4("model", model_);

    //generate send view matrix to shader
    InitializeViewMatrix();
    shader_->SetMat4("view", view_);

    glutSwapBuffers();
}

void Window::WindowResizeCallback(int w, int h) //this is needed because GLUT requires non-member or static member functions
{
    GetActiveWindow()->HandleResize(w, h);
}

void Window::HandleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    window_width_ = w;
    window_height_ = h;
}

void Window::InitializeModelMatrix()
{
    model_ = glm::mat4(1.0f);
    model_ = glm::rotate(model_, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Window::InitializeViewMatrix()
{
    view_ = glm::mat4(1.0f);
    view_ = glm::translate(view_, glm::vec3(0.0f, 0.0f, -3.0f));
}

void Window::InitializeProjectionMatrix()
{
    projection_ = glm::mat4(1.0f);
    projection_ = glm::perspective(glm::radians(45.0f), (float)window_width_/(float)window_height_, 0.1f, 100.0f);
}
