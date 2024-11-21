#include <iostream>
#include <GL/freeglut.h>

#include "config.h"

static void RenderSceneCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main (int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(INITIAL_WINDOW_POSITION);
    int window = glutCreateWindow(WINDOW_NAME); //TODO: move to window class
    std::cout << "Window id: " << window << std::endl;

    //clear all colours
    GLclampf Red = 0.0f, Green = 0.0f, Blue = 0.0f, Alpha = 0.0f;
    glClearColor(Red, Green, Blue, Alpha);

    glutDisplayFunc(RenderSceneCallback);

    glutMainLoop(); // never returns

    return 0;
}