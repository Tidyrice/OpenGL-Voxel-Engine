#include "window.h"
#include <GL/freeglut.h>
#include "controller.h"
#include "scene.h"
#include <iostream>

void Window::CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s)
{
    glutInitWindowSize(w, h);
    glutInitWindowPosition(pos_x, pos_y);
    windowId = glutCreateWindow(window_name.c_str());

    SetScene(s);
}

void Window::RegisterWindowCallbacks()
{
    if (windowId == -1) {
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glUseProgram(shaderProgram);

    // glm::mat4 viewMatrix = scene->GetViewMatrix();
    // glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)windowWidth / windowHeight, 0.1f, 100.0f);
    // glm::mat4 modelMatrix = glm::mat4(1.0f);

    // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
    // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    // glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // glBindVertexArray(VAO);
    // // glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	GLfloat vertices[] = { //equilateral triangle
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

    glutSwapBuffers();
}

void Window::WindowResizeCallback(int w, int h) //this is needed because GLUT requires non-member or static member functions
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

    windowWidth = w;
    windowHeight = h;
}