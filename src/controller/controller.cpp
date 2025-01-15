#include "controller.h"
#include "scene.h"
#include <iostream>
#include "window.h"

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
Controller::UpdateKeyEvents(GLFWwindow* glfw_window)
{
    //checking like this instead of using interrupts for continuous movement

    if (glfwGetKey(glfw_window, GLFW_KEY_W) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_W, GLFW_PRESS);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_A) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_A, GLFW_PRESS);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_S) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_S, GLFW_PRESS);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_D) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_D, GLFW_PRESS);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_SPACE, GLFW_PRESS);
    }
    if (glfwGetKey(glfw_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS);
    }
}

void
Controller::ProcessKeyEventsCallback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if (GetActiveController()) {
        GetActiveController()->HandleKeysInterrupt(key, action);
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
Controller::HandleKeysInterrupt(int key, int action)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        scene_->HandleNormalKeys(GLFW_KEY_ESCAPE, GLFW_PRESS);
    }
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS) { //if we put this in the polling function, it will toggle fullscreen multiple times per key press
        Window::GetActiveWindow()->SetFullScreen(!Window::GetActiveWindow()->IsFullScreen());
    }
}

void
Controller::HandleMouseMovement(double x, double y)
{
    scene_->HandleMouseMovement(x, y);
}