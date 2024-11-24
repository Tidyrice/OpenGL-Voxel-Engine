#include "game_scene.h"
#include <GL/freeglut.h>

void GameScene::HandleRenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glVertex3f(-2,-2,-5.0);
        glVertex3f(2,0.0,-5.0);
        glVertex3f(0.0,2,-5.0);
    glEnd();

    glutSwapBuffers();
}
