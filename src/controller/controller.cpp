#include "controller.h"

Controller* Controller::GetActiveController(Controller* instance)
{
    static Controller* active_controller_instance = nullptr;
    if (instance != nullptr) {
        active_controller_instance = instance;
    }
    return active_controller_instance;
}

void Controller::ProcessNormalKeysCallback(unsigned char key, int x, int y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleNormalKeys(key, x, y);
    }
}

void Controller::ProcessSpecialKeysCallback(int key, int x, int y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleSpecialKeys(key, x, y);
    }
}
