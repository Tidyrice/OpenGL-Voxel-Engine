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
Controller::ProcessKeysCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if (GetActiveController()) {
        GetActiveController()->HandleKeys(key, action);
    }
}

void
Controller::ProcessMouseMovementCallback(GLFWwindow* glfw_window, double x, double y)
{
    if (GetActiveController()) {
        GetActiveController()->HandleMouseMovement(x, y);
    }
}


// ---- PRIVATE METHODS ---- //

void
Controller::HandleKeys(int key, int action)
{
    scene_->HandleNormalKeys(key, action);
}

void
Controller::HandleMouseMovement(double x, double y)
{
    scene_->HandleMouseMovement(x, y);
}