#include "game_controller.h"
#include <GL/freeglut.h>
#include <iostream>

void GameController::HandleNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27: //escape key
            exit(0);
            break;
        case 'w':
            std::cout << "w pressed" << std::endl;
            break;
        case 'a':
            std::cout << "a pressed" << std::endl;
            break;
        case 's':
            std::cout << "s pressed" << std::endl;
            break;
        case 'd':
            std::cout << "d pressed" << std::endl;
            break;
        default:
            break;
    }
}

void GameController::HandleSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            std::cout << "up arrow pressed" << std::endl;
            break;
        case GLUT_KEY_DOWN:
            std::cout << "down arrow pressed" << std::endl;
            break;
        case GLUT_KEY_LEFT:
            std::cout << "left arrow pressed" << std::endl;
            break;
        case GLUT_KEY_RIGHT:
            std::cout << "right arrow pressed" << std::endl;
            break;
        default:
            break;
    }
}