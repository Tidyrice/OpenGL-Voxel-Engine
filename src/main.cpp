#include <glad/glad.h>
#include <GL/freeglut.h>
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitContextVersion(3, 3); // OpenGL 3.3
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    //window initialization
    Window window{WINDOW_WIDTH, WINDOW_HEIGHT, INITIAL_WINDOW_POSITION_X, INITIAL_WINDOW_POSITION_Y, WINDOW_NAME, &scene};
    Window::GetActiveWindow(&window); // set the active window

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
    glutMainLoop(); // never returns

    return 0;
}