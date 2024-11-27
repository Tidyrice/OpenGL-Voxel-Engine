#include <glad/glad.h>
#include "window.h"
#include <GL/freeglut.h>
#include "controller.h"
#include "scene.h"
#include <iostream>

void Window::CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s)
{
    glutInitWindowSize(w, h);
    glutInitWindowPosition(pos_x, pos_y);
    windowId_ = glutCreateWindow(window_name.c_str());

    SetScene(s);
}

void Window::InitializeShaders(const char* vertex_shader_src, const char* fragment_shader_src)
{
    int success;
    char infoLog[512];

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
        std::cerr << "[ERROR]: Vertex shader compilation failed:\n" << infoLog << std::endl;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
        std::cerr << "[ERROR]: Fragment shader compilation failed:\n" << infoLog << std::endl;
    }

    shader_program_ = glCreateProgram();
    glAttachShader(shader_program_, vertex_shader);
    glAttachShader(shader_program_, fragment_shader);
    glLinkProgram(shader_program_);
    glGetProgramiv(shader_program_, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader_program_, 512, NULL, infoLog);
        std::cerr << "[ERROR]: Shader program linking failed:\n" << infoLog << std::endl;
    }
    glUseProgram(shader_program_);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Window::InitializeBuffers()
{
    //some temporary data
    float vertices[] = {
        // positions        // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };   
    GLuint indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
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

    float timeValue = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shader_program_, "color");
    glUseProgram(shader_program_);
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

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
