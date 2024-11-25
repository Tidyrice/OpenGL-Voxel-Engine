#include <glad/glad.h>
#include <GL/freeglut.h>
#include <iostream>

#include "config.h"
#include "window.h"
#include "game_controller.h"
#include "game_scene.h"

Window& window_inst = Window::getInstance();
GameScene scene{};
GameController controller{&scene};

int main (int argc, char* argv[]) {
    Controller::SetActiveControllerInstance(&controller);
    
    //GLUT and window initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitContextVersion(3, 3); // OpenGL 3.3
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    window_inst.CreateAndInitializeWindow(WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          INITIAL_WINDOW_POSITION_X,
                                          INITIAL_WINDOW_POSITION_Y,
                                          WINDOW_NAME,
                                          &scene);

    //GLAD initialization
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //initialize shaders
    // GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    window_inst.RegisterWindowCallbacks();
    glutMainLoop(); // never returns

    return 0;
}