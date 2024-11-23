#include <iostream>
#include <GL/freeglut.h>

#include "config.h"
#include "view/window.h"

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    // window setup
    Window& window_inst = Window::getInstance();
    window_inst.CreateAppWindow(WINDOW_WIDTH, WINDOW_HEIGHT, INITIAL_WINDOW_POSITION_X, INITIAL_WINDOW_POSITION_Y, WINDOW_NAME);
    window_inst.RegisterCallbacks();

    glutMainLoop(); // never returns

    return 0;
}