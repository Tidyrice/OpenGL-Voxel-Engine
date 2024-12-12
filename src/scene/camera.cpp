#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"

void
Camera::GenerateViewMatrix()
{
    view_ = glm::lookAt(camera_pos_, camera_pos_ + camera_front_, world_up_);
}

void
Camera::GenerateProjectionMatrix(int width, int height)
{
    projection_ = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

const glm::mat4&
Camera::GetViewMatrix()
{
    return view_;
}

const glm::mat4&
Camera::GetProjectionMatrix()
{
    return projection_;
}

void
Camera::MoveForward()
{
    camera_pos_ += GetNormalizedCameraSpeed() * camera_front_;
}

void
Camera::MoveBackward()
{
    camera_pos_ -= GetNormalizedCameraSpeed() * camera_front_;
}

void
Camera::MoveLeft()
{
    camera_pos_ -= glm::normalize(glm::cross(camera_front_, camera_up_)) * GetNormalizedCameraSpeed();
}

void
Camera::MoveRight()
{
    camera_pos_ += glm::normalize(glm::cross(camera_front_, camera_up_)) * GetNormalizedCameraSpeed();
}

float
Camera::GetDeltaTime() const
{
    return Window::GetActiveWindow()->GetDeltaTime();
}

float
Camera::GetNormalizedCameraSpeed() const
{
    return camera_speed_ * GetDeltaTime();
}
