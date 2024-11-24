#include <iostream>
#include <GL/freeglut.h>

#include "config.h"
#include "window.h"
#include "game_controller.h"
#include "game_scene.h"

Window& window_inst = Window::getInstance();
GameScene scene{};
GameController controller{&scene};

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    Controller::SetActiveControllerInstance(&controller);

    window_inst.CreateAndInitializeWindow(WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          INITIAL_WINDOW_POSITION_X,
                                          INITIAL_WINDOW_POSITION_Y,
                                          WINDOW_NAME,
                                          &scene);

    glutMainLoop(); // never returns

    return 0;
}