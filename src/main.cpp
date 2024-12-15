#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include "config.h"
#include "window.h"
#include "shader.h"
#include "controller.h"
#include "game_scene.h"

int main(int argc, char* argv[]) {
    GameScene scene{};
    Controller controller{&scene};
    Controller::GetActiveController(&controller); // set the active controller

    
    //GLUT initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //window initialization
    Window window{WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, &scene};
    Window::GetActiveWindow(&window); // set the active window
    glfwMakeContextCurrent(Window::GetActiveGlfwWindowPtr());

    //GLAD initialization
    if (!gladLoadGL()) {
        std::cerr << "[ERROR]: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //GL configuration
    glEnable(GL_DEPTH_TEST);

    //shader initialization
    Shader shader{VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH};
    window.SetShader(&shader);
    window.InitializeBuffers();

    //start rendering
    window.RegisterWindowCallbacks();
    window.SetRenderMode(Window::RenderMode::FILL_MODE);
    while (!glfwWindowShouldClose(Window::GetActiveGlfwWindowPtr())) {
        Window::GetActiveWindow()->RenderScene();
    }


    glfwTerminate();
    return 0;
}