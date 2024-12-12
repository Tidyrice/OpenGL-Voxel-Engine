#include "scene.h"
#include "camera.h"
#include "window.h"

Scene::~Scene() = default; //must define pure virtual destructor

void
Scene::Update()
{
    UpdatePerFrame();
}

const glm::mat4&
Scene::GetModelMatrix() const
{
    return model_;
}

const glm::mat4&
Scene::GetViewMatrix() const
{
    camera_->GenerateViewMatrix();
    return camera_->GetViewMatrix();
}

const glm::mat4&
Scene::GetProjectionMatrix() const
{
    camera_->GenerateProjectionMatrix(Window::GetActiveWindow()->GetWindowWidth(), Window::GetActiveWindow()->GetWindowHeight());
    return camera_->GetProjectionMatrix();
}

float
Scene::GetDeltaTimeMs() const
{
    return Window::GetActiveWindow()->GetDeltaTimeMs();
}
