#include <glad/glad.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <fstream>

#include "config.h"
#include "window.h"
#include "game_controller.h"
#include "game_scene.h"

Window& window_inst = Window::getInstance();
GameScene scene{};
GameController controller{&scene};

std::string ReadFile(std::string filename) {
    std::cout<<filename<<std::endl;
    std::ifstream f(filename);
    std::stringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int main(int argc, char* argv[]) {
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
        std::cerr << "[ERROR]: Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //initialize vertex and fragment shaders
    const char* vertex_shader_code = ReadFile(VERTEX_SHADER_PATH).c_str();
    const char* fragment_shader_code = ReadFile(FRAGMENT_SHADER_PATH).c_str();
    window_inst.InitializeShaders(vertex_shader_code, fragment_shader_code);

    //start rendering
    window_inst.InitializeBuffers();
    window_inst.RegisterWindowCallbacks();
    glutMainLoop(); // never returns

    return 0;
}