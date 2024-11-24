#include "controller.h"

Controller* Controller::active_controller_instance = nullptr; //declaration of static member

void Controller::ProcessNormalKeysCallback(unsigned char key, int x, int y)
{
    if (active_controller_instance) {
        active_controller_instance->HandleNormalKeys(key, x, y);
    }
}

void Controller::ProcessSpecialKeysCallback(int key, int x, int y)
{
    if (active_controller_instance) {
        active_controller_instance->HandleSpecialKeys(key, x, y);
    }
}
