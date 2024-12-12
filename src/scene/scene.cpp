#include "scene.h"
#include "camera.h"
#include "window.h"

Scene::Scene() = default;
Scene::~Scene() = default; //must define pure virtual destructor

const glm::mat4&
Scene::GetModelMatrix() const
{
    return model_;
}

const glm::mat4&
Scene::GetViewMatrix() const
{
    return camera->GetViewMatrix();
}

const glm::mat4&
Scene::GetProjectionMatrix() const
{
    return camera->GetProjectionMatrix();
}

float
Scene::GetDeltaTime() const
{
    return Window::GetActiveWindow()->GetDeltaTime();
}
