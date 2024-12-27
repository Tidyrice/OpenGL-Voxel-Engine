#include "scene.h"
#include "camera.h"
#include "window.h"
#include <stdexcept>

Scene::~Scene() = default; //must define pure virtual destructor

void
Scene::Update()
{
    UpdatePerFrame();
}

glm::mat4
Scene::GetViewMatrix() const
{
    if (Window::GetActiveWindow() == nullptr) {
        throw std::runtime_error("Scene::GetViewMatrix(): Window is not initialized");
    }
    return camera_->GetViewMatrix();
}

glm::mat4
Scene::GetProjectionMatrix() const
{
    if (Window::GetActiveWindow() == nullptr) {
        throw std::runtime_error("Scene::GetProjectionMatrix(): Window is not initialized");
    }
    return camera_->GetProjectionMatrix(Window::GetActiveWindow()->GetWindowWidth(), Window::GetActiveWindow()->GetWindowHeight());
}

float
Scene::GetDeltaTime() const
{
    return Window::GetActiveWindow()->GetDeltaTime();
}
