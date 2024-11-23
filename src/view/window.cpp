#include "window.h"
#include <GL/freeglut.h>
#include "controller.h"

void Window::CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name)
{
    glutInitWindowSize(w, h);
    glutInitWindowPosition(pos_x, pos_y);
    windowId = glutCreateWindow(window_name.c_str());

    RegisterCallbacks();
}

void Window::RegisterCallbacks()
{
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

void Window::RenderSceneCallback() //this is needed because GLUT requires non-member or satatic member functions
{
	getInstance().HandleRenderScene();
}

void Window::HandleRenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
		glVertex3f(-2,-2,-5.0);
		glVertex3f(2,0.0,-5.0);
		glVertex3f(0.0,2,-5.0);
	glEnd();

	glutSwapBuffers();
}


void Window::WindowResizeCallback(int w, int h) //this is needed because GLUT requires non-member or satatic member functions
{
    getInstance().HandleResize(w, h);
}

void Window::HandleResize(int w, int h)
{
    if (h == 0) {
        h = 1;
    }
    float ratio = 1.0* w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45,ratio,1,1000);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}