#include "controller.h"
#include "scene.h"
#include <iostream>

Controller*
Controller::GetActiveController(Controller* instance)
{
    static Controller* active_controller_instance = nullptr;
    if (instance != nullptr) {
        active_controller_instance = instance;
    }
    return active_controller_instance;
}

void
Controller::ProcessNormalKeysCallback(unsigned char key, int x, int y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleNormalKeys(key, x, y);
    }
}

void
Controller::ProcessSpecialKeysCallback(int key, int x, int y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleSpecialKeys(key, x, y);
    }
}

void
Controller::HandleNormalKeys(unsigned char key, int x, int y)
{
    switch (key) {
        case 27: //escape key
            exit(0);
            break;
        case 'w':
            std::cout << "w key pressed" << std::endl;
            scene_->HandleWKeyPress();
            break;
        case 'a':
            std::cout << "a key pressed" << std::endl;
            scene_->HandleAKeyPress();
            break;
        case 's':
            std::cout << "s key pressed" << std::endl;
            scene_->HandleSKeyPress();
            break;
        case 'd':
            std::cout << "d key pressed" << std::endl;
            scene_->HandleDKeyPress();
            break;
        default:
            break;
    }
}

void
Controller::HandleSpecialKeys(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP:
            scene_->HandleWKeyPress(); //using these for now
            break;
        case GLUT_KEY_LEFT:
            scene_->HandleAKeyPress();
            break;
        case GLUT_KEY_DOWN:
            scene_->HandleSKeyPress();
            break;
        case GLUT_KEY_RIGHT:
            scene_->HandleDKeyPress();
            break;
        default:
            break;
    }
}