#include "controller.h"

Controller* Controller::active_controller_instance = nullptr;

void Controller::SetActiveControllerInstance(Controller* controller)
{
    active_controller_instance = controller;
}

void Controller::ProcessNormalKeysCallback(unsigned char key, int x, int y)
{
    active_controller_instance->HandleNormalKeys(key, x, y);
}

void Controller::ProcessSpecialKeysCallback(int key, int x, int y)
{
    active_controller_instance->HandleSpecialKeys(key, x, y);
}
