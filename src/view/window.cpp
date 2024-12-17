#include <glad/glad.h>
#include "window.h"
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

Window::Window(int w, int h, std::string window_name, Scene* s): window_width_{w}, window_height_{h} {
    stbi_set_flip_vertically_on_load(true);

    glfw_window_ptr_ = glfwCreateWindow(w, h, window_name.c_str(), NULL, NULL);
    if (glfw_window_ptr_ == NULL) {
        std::cerr << "Window::Window(): Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }

    SetScene(s);
}

void
Window::RegisterWindowCallbacks()
{
    if (glfw_window_ptr_ == nullptr) {
        std::cerr << "Window::RegisterWindowCallbacks(): window not created yet" << std::endl;
        return;
    }

    //send projection matrix to shader (set here since projecion matrix is constant)
    if (shader_ == nullptr) {
        std::cerr << "Window::RegisterWindowCallbacks(): shader not set" << std::endl;
        return;
    }
    
    shader_->SetMat4("projection", GetProjectionMatrix());

    //TEMP: create texture array
    GLuint texture_arr = scene_->GenerateArrayTexture();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture_arr);
    shader_->SetUniform1i("textureArray", 0);

    //resize callback
    glfwSetFramebufferSizeCallback(glfw_window_ptr_, WindowResizeCallback);

    //handle keyboard input
    glfwSetKeyCallback(glfw_window_ptr_, Controller::ProcessKeysCallback);

    //handle mouse input
    glfwSetInputMode(glfw_window_ptr_, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hide and capture cursor
    glfwSetCursorPosCallback(glfw_window_ptr_, Controller::ProcessMouseMovementCallback);
}

void
Window::SetRenderMode(RenderMode mode)
{
    switch (mode) {
        case RenderMode::FILL_MODE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case RenderMode::WIREFRAME_MODE:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
    }
}

void
Window::RenderScene()
{
    glfwPollEvents();

    UpdateDeltaTime();
    scene_->Update(); //let scene know that there is a new frame

    //clear the screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->UseShader();

    //send model matrix to shader
    shader_->SetMat4("model", GetModelMatrix());

    //send view matrix to shader
    shader_->SetMat4("view", GetViewMatrix());

    //render
    glBindVertexArray(scene_->GetVAO());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); //use EBO

    glfwSwapBuffers(glfw_window_ptr_);
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
Window::WindowResizeCallback(GLFWwindow* glfw_window, int w, int h)
{
    GetActiveWindow()->HandleResize(w, h);
}

void Window::HandleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    window_width_ = w;
    window_height_ = h;
}

const glm::mat4
Window::GetModelMatrix() const
{
    return scene_->GetModelMatrix();
}

const glm::mat4
Window::GetViewMatrix() const
{
    return scene_->GetViewMatrix();
}

const glm::mat4
Window::GetProjectionMatrix() const
{
    return scene_->GetProjectionMatrix();
}

void
Window::UpdateDeltaTime()
{
    float current_frame = glfwGetTime();
    delta_time_ = current_frame - last_frame_;
    last_frame_ = current_frame;
}
