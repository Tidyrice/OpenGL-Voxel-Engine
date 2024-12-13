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
Controller::ProcessMouseMovementCallback(int x, int y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleMouseMovement(x, y);
    }
}

void
Controller::HandleNormalKeys(unsigned char key, int x, int y)
{
    scene_->HandleNormalKeys(key, x, y);
}

void
Controller::HandleSpecialKeys(int key, int x, int y)
{
    
}

void
Controller::HandleMouseMovement(int x, int y)
{
    scene_->HandleMouseMovement(x, y);
}